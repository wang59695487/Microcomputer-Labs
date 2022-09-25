#include<reg52.h>
//#include"DS18B20_3.H"
#include <string.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define wd 1				//?????????  =0????,=1????
#include "eeprom52.h"

#define yh 0x80 //LCD????????,??LCD1602??????D7???1(100000000=80)
#define er 0x80+0x40 //LCD???????(???????????????0x40)

//?????C51?????????(??????C51?P0?)
sbit en=P2^7;
sbit rw=P2^5;   //?????rw??,??????????rw=0?
sbit rs=P2^6;


//?????C51???????

sbit set=P1^3;  	//???
sbit add=P1^4;  	//??
sbit dec=P1^5;  	//??
sbit seeNL_NZ=P3^2;	//????/??

sbit DQ=P3^7;		//
sbit buzzer=P1^7;	//???,?????8550??,??????

bit  led1=1;
bit NZ_sdgb=1;
unsigned char temp_miao;
unsigned char bltime;  //??????

//DS1302?????C51?????????
sbit IO=P3^5;
sbit SCLK=P3^6;
sbit RST=P3^4;


char a,miao,shi,fen,ri,yue,nian,week,setn,temp;
uint flag;
//flag????????????,??????
bit c_moon;

char nz_shi,nz_fen,setNZn;    	//??????
uchar shangyimiao,bsn,temp_hour;			//???????
uchar T_NL_NZ;							//???
bit timerOn=0;							//???????
bit baoshi=0;							//???????
bit  p_r=0;		 						//??/??  =0????,=1????
data uchar year_moon,month_moon,day_moon;

sbit ACC0=ACC^0;
sbit ACC7=ACC^7;
/************************************************************
ACC???=A
ACC.0=E0H 

ACC.0??ACC??0??Acc??????

???ACC???8??????,??????????,?????????????,
??????????????,????????ACC????????????,
??A???????????????,???PUSH???,????ACC??????
?????,A????????????ACC??????????? 
***************************************************************/

/******************???????????eeprom?******************/
void write_eeprom()
{
	SectorErase(0x2000);
	byte_write(0x2000, nz_shi);
	byte_write(0x2001, nz_fen);
	byte_write(0x2002, timerOn);
	byte_write(0x2060, a_a);	
}

/******************?????????eeprom????*****************/
void read_eeprom()
{
	nz_shi   = byte_read(0x2000);
	nz_fen = byte_read(0x2001);
	timerOn = byte_read(0x2002);
	a_a      = byte_read(0x2060);
}

/**************????eeprom???*****************/
void init_eeprom() 
{
	read_eeprom();		//??
	if(a_a != 1)		//????????????eeprom
	{
		nz_shi   = 12;
		nz_fen = 30;
		timerOn=0;
		a_a = 1;
		write_eeprom();	   //????
	}	
}

//********???????************************************
code uchar year_code[597]={
                    0x04,0xAe,0x53,    //1901 0
                    0x0A,0x57,0x48,    //1902 3
                    0x55,0x26,0xBd,    //1903 6
                    0x0d,0x26,0x50,    //1904 9
                    0x0d,0x95,0x44,    //1905 12
                    0x46,0xAA,0xB9,    //1906 15
                    0x05,0x6A,0x4d,    //1907 18
                    0x09,0xAd,0x42,    //1908 21
                    0x24,0xAe,0xB6,    //1909
                    0x04,0xAe,0x4A,    //1910
                    0x6A,0x4d,0xBe,    //1911
                    0x0A,0x4d,0x52,    //1912
                    0x0d,0x25,0x46,    //1913
                    0x5d,0x52,0xBA,    //1914
                    0x0B,0x54,0x4e,    //1915
                    0x0d,0x6A,0x43,    //1916
                    0x29,0x6d,0x37,    //1917
                    0x09,0x5B,0x4B,    //1918
                    0x74,0x9B,0xC1,    //1919
                    0x04,0x97,0x54,    //1920
                    0x0A,0x4B,0x48,    //1921
                    0x5B,0x25,0xBC,    //1922
                    0x06,0xA5,0x50,    //1923
                    0x06,0xd4,0x45,    //1924
                    0x4A,0xdA,0xB8,    //1925
                    0x02,0xB6,0x4d,    //1926
                    0x09,0x57,0x42,    //1927
                    0x24,0x97,0xB7,    //1928
                    0x04,0x97,0x4A,    //1929
                    0x66,0x4B,0x3e,    //1930
                    0x0d,0x4A,0x51,    //1931
                    0x0e,0xA5,0x46,    //1932
                    0x56,0xd4,0xBA,    //1933
                    0x05,0xAd,0x4e,    //1934
                    0x02,0xB6,0x44,    //1935
                    0x39,0x37,0x38,    //1936
                    0x09,0x2e,0x4B,    //1937
                    0x7C,0x96,0xBf,    //1938
                    0x0C,0x95,0x53,    //1939
                    0x0d,0x4A,0x48,    //1940
                    0x6d,0xA5,0x3B,    //1941
                    0x0B,0x55,0x4f,    //1942
                    0x05,0x6A,0x45,    //1943
                    0x4A,0xAd,0xB9,    //1944
                    0x02,0x5d,0x4d,    //1945
                    0x09,0x2d,0x42,    //1946
                    0x2C,0x95,0xB6,    //1947
                    0x0A,0x95,0x4A,    //1948
                    0x7B,0x4A,0xBd,    //1949
                    0x06,0xCA,0x51,    //1950
                    0x0B,0x55,0x46,    //1951
                    0x55,0x5A,0xBB,    //1952
                    0x04,0xdA,0x4e,    //1953
                    0x0A,0x5B,0x43,    //1954
                    0x35,0x2B,0xB8,    //1955
                    0x05,0x2B,0x4C,    //1956
                    0x8A,0x95,0x3f,    //1957
                    0x0e,0x95,0x52,    //1958
                    0x06,0xAA,0x48,    //1959
                    0x7A,0xd5,0x3C,    //1960
                    0x0A,0xB5,0x4f,    //1961
                    0x04,0xB6,0x45,    //1962
                    0x4A,0x57,0x39,    //1963
                    0x0A,0x57,0x4d,    //1964
                    0x05,0x26,0x42,    //1965
                    0x3e,0x93,0x35,    //1966
                    0x0d,0x95,0x49,    //1967
                    0x75,0xAA,0xBe,    //1968
                    0x05,0x6A,0x51,    //1969
                    0x09,0x6d,0x46,    //1970
                    0x54,0xAe,0xBB,    //1971
                    0x04,0xAd,0x4f,    //1972
                    0x0A,0x4d,0x43,    //1973
                    0x4d,0x26,0xB7,    //1974
                    0x0d,0x25,0x4B,    //1975
                    0x8d,0x52,0xBf,    //1976
                    0x0B,0x54,0x52,    //1977
                    0x0B,0x6A,0x47,    //1978
                    0x69,0x6d,0x3C,    //1979
                    0x09,0x5B,0x50,    //1980
                    0x04,0x9B,0x45,    //1981
                    0x4A,0x4B,0xB9,    //1982
                    0x0A,0x4B,0x4d,    //1983
                    0xAB,0x25,0xC2,    //1984
                    0x06,0xA5,0x54,    //1985
                    0x06,0xd4,0x49,    //1986
                    0x6A,0xdA,0x3d,    //1987
                    0x0A,0xB6,0x51,    //1988
                    0x09,0x37,0x46,    //1989
                    0x54,0x97,0xBB,    //1990
                    0x04,0x97,0x4f,    //1991
                    0x06,0x4B,0x44,    //1992
                    0x36,0xA5,0x37,    //1993
                    0x0e,0xA5,0x4A,    //1994
                    0x86,0xB2,0xBf,    //1995
                    0x05,0xAC,0x53,    //1996
                    0x0A,0xB6,0x47,    //1997
                    0x59,0x36,0xBC,    //1998
                    0x09,0x2e,0x50,    //1999 294
                    0x0C,0x96,0x45,    //2000 297
                    0x4d,0x4A,0xB8,    //2001
                    0x0d,0x4A,0x4C,    //2002
                    0x0d,0xA5,0x41,    //2003
                    0x25,0xAA,0xB6,    //2004
                    0x05,0x6A,0x49,    //2005
                    0x7A,0xAd,0xBd,    //2006
                    0x02,0x5d,0x52,    //2007
                    0x09,0x2d,0x47,    //2008
                    0x5C,0x95,0xBA,    //2009
                    0x0A,0x95,0x4e,    //2010
                    0x0B,0x4A,0x43,    //2011
                    0x4B,0x55,0x37,    //2012
                    0x0A,0xd5,0x4A,    //2013
                    0x95,0x5A,0xBf,    //2014
                    0x04,0xBA,0x53,    //2015
                    0x0A,0x5B,0x48,    //2016
                    0x65,0x2B,0xBC,    //2017
                    0x05,0x2B,0x50,    //2018
                    0x0A,0x93,0x45,    //2019
                    0x47,0x4A,0xB9,    //2020
                    0x06,0xAA,0x4C,    //2021
                    0x0A,0xd5,0x41,    //2022
                    0x24,0xdA,0xB6,    //2023
                    0x04,0xB6,0x4A,    //2024
                    0x69,0x57,0x3d,    //2025
                    0x0A,0x4e,0x51,    //2026
                    0x0d,0x26,0x46,    //2027
                    0x5e,0x93,0x3A,    //2028
                    0x0d,0x53,0x4d,    //2029
                    0x05,0xAA,0x43,    //2030
                    0x36,0xB5,0x37,    //2031
                    0x09,0x6d,0x4B,    //2032
                    0xB4,0xAe,0xBf,    //2033
                    0x04,0xAd,0x53,    //2034
                    0x0A,0x4d,0x48,    //2035
                    0x6d,0x25,0xBC,    //2036
                    0x0d,0x25,0x4f,    //2037
                    0x0d,0x52,0x44,    //2038
                    0x5d,0xAA,0x38,    //2039
                    0x0B,0x5A,0x4C,    //2040
                    0x05,0x6d,0x41,    //2041
                    0x24,0xAd,0xB6,    //2042
                    0x04,0x9B,0x4A,    //2043
                    0x7A,0x4B,0xBe,    //2044
                    0x0A,0x4B,0x51,    //2045
                    0x0A,0xA5,0x46,    //2046
                    0x5B,0x52,0xBA,    //2047
                    0x06,0xd2,0x4e,    //2048
                    0x0A,0xdA,0x42,    //2049
                    0x35,0x5B,0x37,    //2050
                    0x09,0x37,0x4B,    //2051
                    0x84,0x97,0xC1,    //2052
                    0x04,0x97,0x53,    //2053
                    0x06,0x4B,0x48,    //2054
                    0x66,0xA5,0x3C,    //2055
                    0x0e,0xA5,0x4f,    //2056
                    0x06,0xB2,0x44,    //2057
                    0x4A,0xB6,0x38,    //2058
                    0x0A,0xAe,0x4C,    //2059
                    0x09,0x2e,0x42,    //2060
                    0x3C,0x97,0x35,    //2061
                    0x0C,0x96,0x49,    //2062
                    0x7d,0x4A,0xBd,    //2063
                    0x0d,0x4A,0x51,    //2064
                    0x0d,0xA5,0x45,    //2065
                    0x55,0xAA,0xBA,    //2066
                    0x05,0x6A,0x4e,    //2067
                    0x0A,0x6d,0x43,    //2068
                    0x45,0x2e,0xB7,    //2069
                    0x05,0x2d,0x4B,    //2070
                    0x8A,0x95,0xBf,    //2071
                    0x0A,0x95,0x53,    //2072
                    0x0B,0x4A,0x47,    //2073
                    0x6B,0x55,0x3B,    //2074
                    0x0A,0xd5,0x4f,    //2075
                    0x05,0x5A,0x45,    //2076
                    0x4A,0x5d,0x38,    //2077
                    0x0A,0x5B,0x4C,    //2078
                    0x05,0x2B,0x42,    //2079
                    0x3A,0x93,0xB6,    //2080
                    0x06,0x93,0x49,    //2081
                    0x77,0x29,0xBd,    //2082
                    0x06,0xAA,0x51,    //2083
                    0x0A,0xd5,0x46,    //2084
                    0x54,0xdA,0xBA,    //2085
                    0x04,0xB6,0x4e,    //2086
                    0x0A,0x57,0x43,    //2087
                    0x45,0x27,0x38,    //2088
                    0x0d,0x26,0x4A,    //2089
                    0x8e,0x93,0x3e,    //2090
                    0x0d,0x52,0x52,    //2091
                    0x0d,0xAA,0x47,    //2092
                    0x66,0xB5,0x3B,    //2093
                    0x05,0x6d,0x4f,    //2094
                    0x04,0xAe,0x45,    //2095
                    0x4A,0x4e,0xB9,    //2096
                    0x0A,0x4d,0x4C,    //2097
                    0x0d,0x15,0x41,    //2098
                    0x2d,0x92,0xB5,    //2099
};

///?????
code uchar day_code1[9]={0x0,0x1f,0x3b,0x5a,0x78,0x97,0xb5,0xd4,0xf3};
code uint day_code2[3]={0x111,0x130,0x14e};

/*
????:??BCD????,??BCD????(???1901-2099?)
??????:Conversion(c_sun,year_sun,month_sun,day_sun)
?:??2004?10?16?Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun??BCD??,c_sun??????,c_sun=0?21?
?,c_sun=1?19??
?????,??????,?c_moon,year_moon,month_moon,day_moon????BCD??
*/

bit c_moon;
//???,?????????????????,????????1,????0
bit get_moon_day(uchar month_p,uint table_addr)
{
	uchar temp10;
    switch (month_p){
        case 1:{temp10=year_code[table_addr]&0x08;
             if (temp10==0)return(0);else return(1);}
        case 2:{temp10=year_code[table_addr]&0x04;
             if (temp10==0)return(0);else return(1);}
        case 3:{temp10=year_code[table_addr]&0x02;
             if (temp10==0)return(0);else return(1);}
        case 4:{temp10=year_code[table_addr]&0x01;
             if (temp10==0)return(0);else return(1);}
        case 5:{temp10=year_code[table_addr+1]&0x80;
             if (temp10==0) return(0);else return(1);}
        case 6:{temp10=year_code[table_addr+1]&0x40;
             if (temp10==0)return(0);else return(1);}
        case 7:{temp10=year_code[table_addr+1]&0x20;
             if (temp10==0)return(0);else return(1);}
        case 8:{temp10=year_code[table_addr+1]&0x10;
             if (temp10==0)return(0);else return(1);}
        case 9:{temp10=year_code[table_addr+1]&0x08;
             if (temp10==0)return(0);else return(1);}
        case 10:{temp10=year_code[table_addr+1]&0x04;
             if (temp10==0)return(0);else return(1);}
        case 11:{temp10=year_code[table_addr+1]&0x02;
             if (temp10==0)return(0);else return(1);}
        case 12:{temp10=year_code[table_addr+1]&0x01;
             if (temp10==0)return(0);else return(1);}
        case 13:{temp10=year_code[table_addr+2]&0x80;
             if (temp10==0)return(0);else return(1);}
		default:return(2);
    }
}

/*
????:??BCD????,??BCD????(???1901-2099?)
??????:Conversion(c_sun,year_sun,month_sun,day_sun)
?:??2004?10?16?Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun??BCD??,c_sun??????,c_sun=0?21?
?,c_sun=1?19??
?????,??????,?c_moon,year_moon,month_moon,day_moon????BCD??
*/

void Conversion(bit c,uchar year,uchar month,uchar day)
{                         //c=0 ?21??,c=1 ?19?? ????????BCD??
    uchar temp1,temp2,temp3,month_p;
    uint temp4,table_addr;
    bit flag2,flag_y;
    temp1=year/16;   //BCD->hex ???????????
    temp2=year%16;
   // year=temp1*10+temp2;
	year=temp1*16+temp2;
    temp1=month/16;
    temp2=month%16;
    //month=temp1*10+temp2;
	month=temp1*16+temp2;
    temp1=day/16;
    temp2=day%16;
    //day=temp1*10+temp2;
	day=temp1*16+temp2;
    //???????
    if(c==0){                   
        table_addr=(year+0x64-1)*0x3;
    }
    else {
        table_addr=(year-1)*0x3;
    }
    //?????????
    //????????????
    temp1=year_code[table_addr+2]&0x60; 
    temp1=_cror_(temp1,5);
    //??????????????
    //???????????
    temp2=year_code[table_addr+2]&0x1f; 
    //?????????????
    // ??????????????,???????1??2?
    if(temp1==0x1){  
        temp3=temp2-1;  
    }  
    else{
        temp3=temp2+0x1f-1;        
    }
    // ????????????????
    //?????????????,??????,?????
    //day_code1[9],day_code2[3]
    //??????????,?????0xff,??day_code1[9],
    //????,????0xff,??day_code2[3]
    //???????8?10?,??????????day_code1[8-1]+10-1
    //???????11?10?,??????????day_code2[11-10]+10-1
    if (month<10){ 
        temp4=day_code1[month-1]+day-1;
    }
    else{
        temp4=day_code2[month-10]+day-1;
    }
    if ((month>0x2)&&(year%0x4==0)){  //???????2??????2????,???1
        temp4+=1;
    }
    //???????????????
    //??????????????
    if (temp4>=temp3){ //????????????????????????
        temp4-=temp3;
        month=0x1;
        month_p=0x1;  //month_p?????,??????????????month_p????
        flag2=get_moon_day(month_p,table_addr); //?????????????,????1,????0
        flag_y=0;
        if(flag2==0)temp1=0x1d; //??29?
        else temp1=0x1e; //??30?
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);  //?????????????,??0??????
        while(temp4>=temp1){
            temp4-=temp1;
            month_p+=1;
            if(month==temp2){
            flag_y=~flag_y;
            if(flag_y==0)month+=1;
            }
            else month+=1;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)temp1=0x1d;
            else temp1=0x1e;
        }
        day=temp4+1;
    }
    else{  //?????????????????
        temp3-=temp4;
        if (year==0x0){year=0x63;c=1;}
        else year-=1;
        table_addr-=0x3;
        month=0xc;
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);
        if (temp2==0)
			month_p=0xc; 
        else
			month_p=0xd; //
        
       	 //month_p?????,???????,???????,???13,?????12
        
        flag_y=0;
        flag2=get_moon_day(month_p,table_addr);
        if(flag2==0)temp1=0x1d;
        else temp1=0x1e;
        while(temp3>temp1){
            temp3-=temp1;
            month_p-=1;
            if(flag_y==0)month-=1;
            if(month==temp2)flag_y=~flag_y;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)temp1=0x1d;
            else temp1=0x1e;
         }
        day=temp1-temp3+1;
    }
    c_moon=c;                 //HEX->BCD ,?????,??????BCD??
    temp1=year/10;
    temp1=_crol_(temp1,4);
    temp2=year%10;
    year_moon=temp1|temp2;
    temp1=month/10;
    temp1=_crol_(temp1,4);
    temp2=month%10;
    month_moon=temp1|temp2;
    temp1=day/10;
    temp1=_crol_(temp1,4);
    temp2=day%10;
    day_moon=temp1|temp2;
}


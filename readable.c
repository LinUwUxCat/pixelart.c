#include <stdio.h>
c; //char
i;
l=0;s=0; //longest line count and current line size
r=0; //number of lines
e;d;o; //size

a[255][3];
P(X){putchar(X);}
main(_,v)char**v;{ //int main(int argc, char** argv){
    FILE*f=fopen(v[1],"r"); //open file
    srand(atoi(v[2]));
    while(c!=-1){ //EOF
        c=getc(f);
        if(c==10){ //\n
            r++;
            if(s>l)l=s;
            s=0;
        }else++s;
        if(!a[c][0]){
            for(i=0;i<3;i++){
                a[c][i]=rand()%256+1; //we do this because we want values from 0 to 255 but we use 0 as our uninitialised array value.
            }
        }
    }
    r++;
    s--;
    if(s>l)l=s;
    // Padding is necessary to make sure we have our row with a number of bytes that's a multiple of 4.
    // There are 2 solutions:
    // - Using 32bpp, which requires no padding at all considering a pixel is always 4 bytes.
    //   However that one requires to add an FF after each RGB (we want no transparency), and 00 4 times for each empty pixels.
    //   We can calculate the number of empty pixels easily by counting the number of pixels we write, then when we encounter a LF,
    //   we substract that number to the longest line size. the number of 00 bytes left to add is that * 4.
    // - Using 24bpp, which unfortunately requires a padding, but we can avoid putting FF after each RGB value.
    //   To calculate the amount of 00 bytes we have to add, we need to count the number of BYTES we write this time.
    //   then we need to multiply l by 3 and round it to the nearest multiple of 4, like so:
    //   l=((l / 4) + (l % 4 > 0)) * 4      // Thanks to Like4Schnitzel for helping me do this
    //   note : l is the longest line count
    //   And only then we can substract our number of bytes written to l

    // Strategy 2 first
    //l--; //?
    o=((l*3 / 4) + (l*3 % 4 > 0)) * 4; // THis is the longest line size in BYTES
    e=54+o*r;
    r=-r;
    d=e-54;
    c=0;
    s=0;
    char h[]={66,77, //BMP magic
    e&255,e>>8&255,e>>16&255,e>>24&255, //file size (o*r + header)
    0,0,0,0, // any bullshit
    54,0,0,0, //offset where data starts (1 byte after end of header)
    40,0,0,0, //size of BITMAPINFOHEADER
    l&255,l>>8&255,l>>16&255,l>>24&255, //Width of image
    r&255,r>>8&255,r>>16&255,r>>24&255, //height of image
    1,0, //must always be 1 for whatever reason
    24,0, //color depth - bits per pixel
    0,0,0,0, //compression method - here uncompressed
    d&255,d>>8&255,d>>16&255,d>>24&255, //size of data (pixels)
    19,11,0,0,19,11,0,0, //pixels per metre (why is this important?) anyways who cares
    0,0,0,0, //colors in the palette (0 = default = 2^24, which is what we want here)
    0,0,0,0 //important colors (0 = all of em)
    }; //end of header
    fseek(f,0,SEEK_SET);
    for (i=0;i<54;i++)P(h[i]);
    while(c!=-1){ //EOF
        c=getc(f);
        if(c!=10&&c!=-1){
            for(i=0;i<3;i++){
                P(a[c][i]-1);
                s++;
            }
        }else{
            for(;s<o;s++){//should do the same as for(i=0;i<o-s;i++)
                P(0);
            }
            s=0;
        }
    }
    // I have not done strategy 1 yet
}
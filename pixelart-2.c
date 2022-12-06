f,c,i,l=0,s=0,r=0,e,d,o,k=255;a[255][3
];P(X){putchar(X);}main(_,v)char**v;{f
=open(v[1],0);srand(atoi(v[2]));while(
read(f,&c,1)){if(c==10){++r;if(s>l)l=s
;s=0;}else++s;if(!a[c][0])for(i=0;i<3;
++i)a[c][i]=rand()%k+2;}if(--s>l)l=s;o
=((l*3/4)+(l*3%4>0))*4;e=54+o*r++;r=-r
;d=e-54;c=s=i=0;int h[54]={66,77,e&k,e
>>8&k,e>>16&k,e>>24&k,0,0,0,0,54,0,0,0
,40,0,0,0,l&k,l>>8&k,l>>16&k,l>>24&k,r
&k,r>>8&k,r>>16&k,r>>24&k,1,0,24,0,0,0
,0,0,d&k,d>>8&k,d>>16&k,d>>24&k,19,11,
0,0,19,11};lseek(f,0,0);for(;i<54;i++)
P(h[i]);while(read(f,&c,1)){if(c!=10)
for(i=0;i<3;i++){P(a[c][i]-1);s++;}else
{for(;s<o;s++)P(0);s=0;}}for(;s<o;s++)
P(0);close(f);}
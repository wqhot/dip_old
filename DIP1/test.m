clear;
sizen=16;

for i=1:sizen
    for j=1:sizen
        n(i,j)=cos((i-1)*(2*j-1)*pi/2/sizen);
        k=floor((i-1)*(2*j-1)/2/sizen);
        a(i,j)=((i-1)*(2*j-1)*pi/2/sizen-k*pi);
        %nn(i,j)=cos(a(i,j))*(-1)^k;
        aa(i,j)=(i-1)*(2*j-1);
        k=floor(aa(i,j)/2/sizen);
        aa(i,j)=aa(i,j)-k*sizen*2;
        nn(i,j)=cos(aa(i,j)*pi/2/sizen)*(-1)^k;
    end
end
 unique(aa(:))'
 
 for i=1:20
     a(i)=cos((i-1)*pi/20);
 end
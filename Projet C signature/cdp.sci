function dist=d(i, j,table1,table2)
somme=0;
    i=i-2;
    for k=1:size(table1,1)
       somme=somme+(table1(k,i)-table2(k,j))*(table1(k,i)-table2(k,j))
    end
    dist=sqrt(somme);
    return dist
endfunction


function p=cdp(test, ref)
    
    t=size(test,2);
    to=size(ref,2);
    p=zeros(t+2,to);

    for j=1:to
        p(1,j)=9999;
    end
    for j=1:to
        p(2,j)=9999;
    end
    //Attention plus de normalisation ici !!*/
    for i=3:t+2
        
        p(i,1)=3*d(i,1,test,ref);
        if i<=3  then
            p(i,2)= min((p(i-1,1)+d(i,2,test,ref)),(p(i,1)+d(i,2,test,ref)));
            else
            p(i,2)= min((p(i-2,1)+d(i-1,2,test,ref)+d(i,2,test,ref)),(p(i-1,1)+d(i,2,test,ref)),(p(i,1)+d(i,2,test,ref)));
        end
                    
        for j=3:to
            if i<=3  then
                   p(i,j)= min((p(i-1,j-1)+d(i,j,test,ref)),(p(i-1,j-2)+d(i,j-1,test,ref)+d(i,j,test,ref)));
               else
                   p(i,j)= min((p(i-2,j-1)+d(i-1,j,test,ref)+d(i,j,test,ref)),(p(i-1,j-1)+d(i,j,test,ref)),(p(i-1,j-2)+d(i,j-1,test,ref)+d(i,j,test,ref)));
            end

        end

    end
    return p
endfunction


function A=cdp2(p,test,ref)
    t=size(test,2);
    to=size(ref,2);
    A=zeros(t)
    for i=1:t
        A(i)=(1/(3*to))*p(i+2,to);
    end

    return A
endfunction

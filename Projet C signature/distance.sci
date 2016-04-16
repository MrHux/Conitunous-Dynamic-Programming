function dist=distance(i, j,table1,table2)
somme=0;
    for k=1:size(table1,1)
       somme=somme+(table1(k,i)-table2(k,j))*(table1(k,i)-table2(k,j));
    end
    dist=sqrt(somme);
    return dist
endfunction

function matDesDist=distanceMatrice(table1, table2)
    tailleTable1=size(table1,2);
    tailleTable2=size(table2,2);
    matDesDist=zeros(tailleTable1, tailleTable2);
    for i=1:tailleTable1
        for j=1:tailleTable2
               matDesDist(i,j)=distance(i,j,table1,table2);
        end
    end
return matDesDist;

endfunction

function dtw=dynamic(table1, table2)
    n=size(table1,2)+1;
    m=size(table2,2)+1;
    dtw=zeros(n,m);
    matricedistances=distanceMatrice(table1,table2);
    for i=1:n
        dtw(i,1)=9999;
    end
    for i=1:m
        dtw(1,i)=9999;
    end
    dtw(1,1) = 0;
    
    for i=2:n
        for j=2:m
                dtw(i,j)=matricedistances(i-1,j-1)+min(dtw(i-1,j),dtw(i-1,j),dtw(i-1,j-1));
       end
    end
return dtw
endfunction



1. The features are calculated from each column of pixel of the images
2.
From each column, we calculate 14 features.


In each cell of this matrix, you can see the following data structure :


1st Cell		
2nd Cell		
3rd Cell			
4th Cell
-------- --------
reference image matrix feature matrix column number of the image, from where feature is calculated	




For example, say the reference image is having 46 ROWS and  217 COLUMNS, so the above mentioned 2nd Cell will contain a matrix of 46*217.

For calculating the feature values, we only consider those column which is having at least one foreground pixel and we ignore those column which don't have any foreground pixels. 
So, obviously total number of rows in feature matrix (one row correspond to one feature vector for one column) will be always less than equals to 217.
Say the size of the feature matrix is 190*14.
 It can be easily understandable that each row in the feature matrix is actually representing the features extracted from each column of the image. 
Feature matrix always has 14 columns (dimension of the vectors in the sequence)


So the afore mentioned 4th cell is actually storing the column numbers, which contain at least one foreground pixel of the image respectively. 
From these columns, we actually obtaining the features.  


Please remember, we always calculate 14 features from each column 

For having the better match, we always normalize the query image for matching with particular target image. 
For normalization, we make the number of rows in query image and in the target image always equal by keeping the aspect ratio same. 
This is why, we need to calculate the feature values for the same query image for each target because to match the query- 
image with seperate target images we need to make the height of query image equal to target image. 
So the size of query image changes each time according to the size of target image, hence number of columns in the query image also gets changed accordingly.
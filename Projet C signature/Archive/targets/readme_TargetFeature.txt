Now we are in "Feature" folder of "TargetImage_Feature"   argetImage_Feature -> Feature
You can see the target images from "Target Img" folder

In the feaure matrix, the data structure is as follows :
i. 1st cell : Feature Matrix
ii. 2nd cell : coulmn number of the image, from where the features are extracted.
iii. 3rd cell : 
iv. 4th cell : the image path of each target images

Say we have a target image of size 78 ROWS and 234 COLS. So as explaiened earlier also, we consider only those column which is haiving atleast one fore ground pixel. Size of the feature matrix will be always less than equal to the number of coulmns present in the image. Say the size of the feture matrix in 202*14. This feature matrix is stored in 2nd cell.

In the 3rd cell, you will find all entry are 0 but the last non zero entry is the number of rows present in the image.

In the 4th cell, you can find complete path of the target image in my computer (I know, it is not useful for you, but you can recognise the image by it's name.)  
 

#include "PSNR.h"
#include <iostream>
#include <math.h>

using namespace std;

double checkMSE(BMP* original, BMP* modified){
	//m x n = width x height
	double MSE = 0;
	//Values for image width and height
	int originalWidth = original -> TellWidth();
	int originalHeight = original -> TellHeight();
	int modifiedWidth = modified -> TellWidth();
	int modifiedHeight = modified -> TellHeight();
	cout<<"Width: "<<original -> TellWidth()<<endl;
	
	for(int i=0; i<originalWidth-1; ++i)
		for(int j=0; j<originalHeight-1; ++j){
			RGBApixel originalPixel = original -> GetPixel(i,j);
			RGBApixel  modifiedPixel = modified -> GetPixel(i,j);
			//Value for image pixels
			double originalRed = (double) originalPixel.Red;
			double originalGreen = (double) originalPixel.Green;
			double originalBlue = (double) originalPixel.Blue;
			double modifiedRed = (double) modifiedPixel.Red;
			double modifiedGreen = (double) modifiedPixel.Green;
			double modifiedBlue = (double) modifiedPixel.Blue;
			MSE += pow((modifiedRed - originalRed),2) + pow((modifiedGreen - originalGreen),2) + pow((modifiedBlue - originalBlue),2);
		}
	MSE = MSE; //* (1 / (3 * originalWidth * originalHeight));
	return MSE;
}

double checkPSNR(BMP* original, BMP* modified){
	int maxRGBValue = 255 * 3;
	double MSE = checkMSE(original, modified);
	//cout<<"MSE: "<<MSE<<endl;
	//If images are the same return 0
	if(MSE == 0){
		return 0;
	}
	double PSNR = (20 * log10(maxRGBValue)) - (10 * log10(MSE));
	return PSNR;
}

// int main(){
	// BMP image;
	// image.ReadFromFile("lena.bmp");
	// cout<<checkPSNR(image, image)<<endl;
	// cout<<"DONE"<<endl;
// }

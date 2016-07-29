#include "gtest/gtest.h"
#include "steganography.h"
#include "EasyBMP.h"

string image1Gray = "EasyBMPbackground.bmp";
string image2RGB = "EasyBMPbackground2.bmp";
string image1GrayModified = "output3.bmp";
string image2RGBModified = "output4.bmp";

TEST (Image, isSameImage)
{
EXPECT_EQ(sameImage(image1Gray, image1Gray, true), true);
EXPECT_EQ(sameImage(image1Gray, image2RGB, false), false);
EXPECT_EQ(sameImage(image1Gray, image1GrayModified, true), false);
}

TEST (NullImage, isSameImage)
{
BMP null;
BMP image1Gray;
BMP image2RGB;
image1Gray.ReadFromFile( image1Gray.c_str() );
image2RGB.ReadFromFile( image2RGB.c_str() );

EXPECT_EQ(nullImage(null, 1, true), false);
EXPECT_EQ(nullImage(image1Gray, 1, true), true);
EXPECT_EQ(nullImage(image1Gray, 2, true), true);
EXPECT_EQ(nullImage(image2RGB, 1, false), true);
EXPECT_EQ(nullImage(image2RGB, 2, false), true);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

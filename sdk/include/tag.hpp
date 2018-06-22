/*
* tag.hpp
*
*  Created on: Nov 05, 2017
*      Author: gyz
*/

#ifndef AIP_TAG_HPP
#define AIP_TAG_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

namespace aip
{

typedef struct tagTagInfo
{
	int code;
	RotatedRect rbox;
	bool appendedFlag;
	bool fromIR;

	tagTagInfo()
	{
		appendedFlag = false;
		fromIR = true;
	}
} TagInfo;

/************************************ Tag Class ************************************/

/** @brief Class for IR tag. See simu_tag.cpp in the AIP sample directory.
*/
class CV_EXPORTS Tag
{
private:
	int rows;
	int cols;
	int parities;
	bool isSquare;
	int codeMax;
	int margin;
	int cellSize;
	int bits;
	int decodeThresh;
	Point2f canvasVertex[3];

public:
	Mat canvas;
	vector<TagInfo> tags;

	Tag();
	virtual ~Tag();

	/** @brief Initialize the tag with essential parameters.
	@param rows The number of rows of the tag cells.
	@param cols The number of columns of the tag cells.
	@param cellSize The side length (pixel) of cell of the tag image.
	@param parities The number of parity bit.
	*/
	void Init(int rows, int cols, int margin, int cellSize, int parities, float thresh);

	/** @brief Encode the tag image.
	@param code The code to generate the tag image.
	*/
	void Encode(int code);

	/** @brief Decode the tag image.
	@param image Grayscale image contains the tags to be decoded,
	@param roi Decode roi,
	@param scale Scale down to speed up,
	@param minArea The minimum area threshold,
	@param maxArea The maximum area threshold.
	*/
	void Decode(const Mat &src, const Rect &roi, double minArea, double maxArea, double scale = 1., double thresh = 80.);

	/** @brief Extend the canvas image to avoid clip after rotation.
	@return The extended canvas image.
	*/
	Mat ExtendCanvas();
};

} // aip

#endif

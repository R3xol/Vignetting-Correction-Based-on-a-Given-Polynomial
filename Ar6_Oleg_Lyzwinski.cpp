#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string> 

using namespace std;
using namespace cv;

int main()
{
	//wczytanie obrazu i skopiowanie go, aby nie modyfikować oryginału
	string path = "W_1.jpg";
	Mat image = imread(path, IMREAD_COLOR); //IMREAD_COLOR gdy obraz jest 3 kanałowy IMREAD_GREYSCALE gdy czarnobiały
	Mat image_corrected = image.clone();

	//definicja wymiarów obrzau oraz jego środka
	int width = image.cols;
	int height = image.rows;
	int middle_width = width / 2;
	int middle_height = height / 2;

	//sprawdzenie ilości kanałów zjęcia
	int image_channels = image.channels();

	//definicja oraz wprowadzenie współczynników wielomianu
	cout << "Wprowadz cztery wspolczynniki wielomianu trzeciego stopnia(a, b, c, d gdzie ax^3 + bx^2 + cx + d):" << endl;
	float a, b, c, d;
	cin >> a >> b >> c >> d;
	cout << "Wielomian korekcji winietowania:" << endl << a << "x^3 + " << b << "x^2 + " << c << "x + " << d << endl;

	//korekcja winietowania dla obrazu jednkanałowego
	if (image_channels == 1) {
		float center_distance, polynomial;
		uchar intens;
		for (int h = 0; h < height; h++) {		
			for (int w = 0; w < width; w++) {
				//wyznaczenie odległości punktu od środka oraz oblicznie wartości wielomianu
				center_distance = sqrt(pow((w - middle_width),2) + pow((h - middle_height),2));
				polynomial = a * pow(center_distance, 3) + b * pow(center_distance, 2) + c * center_distance + d;
				
				//przemnożenie intensywności piksela przez wielomian
				intens = image.at<uchar>(h, w);				
				intens = intens * polynomial;
				
				//zabezpieczenie przed wyjściem poza zakres
				if (intens > 255)
					intens = 255;

				image_corrected.at<uchar>(h, w) = { intens };
			}
		}
	}

	//korekcja winietowania dla obrazu 3 kanałowego
	if (image_channels == 3) {
		float center_distance, polynomial;
		Vec3b intens;
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				//wyznaczenie odległości punktu d środka oraz oblicznie wartości wielomianu
				center_distance = sqrt(pow((w - middle_width),2) + pow((h - middle_height),2));
				polynomial = a * pow(center_distance, 3) + b * pow(center_distance, 2) + c * center_distance + d;

				intens = image.at<Vec3b>(h, w);			
				//zmiana intensywności przez przemnożenie przez wielomian dla 3 kanałów 
				for (int ch = 0; ch < 3; ch++) {
					intens(ch) = intens(ch) * polynomial;
					//zabezpieczenie przed wyjściem poza zakres
					if (intens(ch) >= 255)
						intens(ch) = 255;
				}
				image_corrected.at<Vec3b>(h, w) = { intens };
			}
		}
	}
	//zapis poprawionego obrazu do pliku
	imwrite("Corrected_image.jpg", image_corrected);

	return 0;
}



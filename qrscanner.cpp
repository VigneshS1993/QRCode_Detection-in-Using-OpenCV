#include "qrscanner.h"

using std::make_pair;
using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::vector;
using std::basic_string;
using zbar::Image;
using zbar::ImageScanner;
using namespace cv;
using namespace zbar;

QRScanner::QRScanner() :
    _locations{}
{
//    cv::namedWindow("window");
    // configure the reader
    _scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
}

std::pair<int, int> QRScanner::find(std::string locationName)
{
    auto pos = std::make_pair(int(-1), int(-1));   
    _locMtx.lock();
    for (auto &loc : _locations) {
        if (loc.name == locationName) {
            pos.first  = loc.position.x;
            pos.second = loc.position.y;
            break;
        }
    }
    _locMtx.unlock();
    return pos;
}

void QRScanner::scan(cv::Mat &frame, const vector<string>& locationlist)
{
    cv::Mat imGray;
    if(frame.empty())
    {
        std::cout<<"Frame is empty\n";
    }
    cv::cvtColor(frame, imGray,cv::COLOR_BGR2GRAY);

    // wrap image data
    Image image(imGray.cols, imGray.rows, "Y800", imGray.data, imGray.cols * imGray.rows);

    // scan the image for barcodes
    _scanner.scan(image);
    // extract results
    _locMtx.lock();
    _locations.clear();
    Location location, location1;
    bool match { false };
    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
        location.name = symbol->get_data();
        int num = symbol->get_location_size();
        /*Extract QR Code co-ordinates
         To calculate the midpoint of the qr code, take diagonal co-ordinates and divide them bz 2  */
        for (int i = 0; i < num; i++) {
            if(i == 0 || i == 2)
            {
                location.position.x += symbol->get_location_x(i)/2;;
                location.position.y += symbol->get_location_y(i)/2;;
            }
        }
        //Check for Unrecognized QR-Codes
        for(auto &lname : locationlist)
        {
            if(lname.compare(location.name)==0)
                  match = true;
        }
       if(match){ 
           std::cout<<"Scanned QR Code data - "<<location.name<<" at ("<<location.position.x<<","<<location.position.y<<")\n";
           _locations.push_back(Location(location));
       }else
           std::cout<<"UNRECOGNIZED QR Code data : "<<location.name<<" at ("<<location.position.x<<","<<location.position.y<<")\n"; 
    }
    _locMtx.unlock();
    image.set_data(nullptr, 0);
//    imshow("window", frame);
    cv::waitKey(30);
}

#include "models/image.hpp"

#include <iostream>
#include <string>

#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;
using namespace std;

// Tower exception
struct tower_error: virtual boost::exception { };

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Image::Image(const ptree& pt)
{
  try
  {
    mPhotographer = pt.get<std::string>("photographer");
    mSource = pt.get<std::string>("source");
    mUsername = pt.get<std::string>("username");
    mLicense = pt.get<std::string>("license");

    //cout << "description: " << mDescription << endl;
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not read the Image configuration description" << endl;
    return;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Image::Image(Image& image)
{
  mPhotographer = image.getPhotographer();
  mSource = image.getSource();
  mUsername = image.getUsername();
  mLicense = image.getLicense();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Image::getPhotographer() const
{
  return mPhotographer;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Image::getSource() const
{
  return mSource;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Image::getUsername() const
{
  return mUsername;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Image::getLicense() const
{
  return mLicense;
}





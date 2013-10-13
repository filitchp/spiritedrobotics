#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>

//------------------------------------------------------------------------------
// Describes meta data for a menu image (mostly used for attribution)
//------------------------------------------------------------------------------
class Image
{
  public:

    Image(const boost::property_tree::ptree& pt);

  private:

    std::string mPhotographer;
    std::string mSource;
    std::string mUsername;
    std::string mLicense;

};

#endif // IMAGE_HPP

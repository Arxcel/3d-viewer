#pragma once
#include <string>

#define PATHKEEPER PathKeeper::getInstance()
class PathKeeper
{
  public:
    static PathKeeper& getInstance()
    {
        static PathKeeper pk;
        return pk;
    }
    void setBinFolder(std::string &aNewBin)
    {
        mBinFolder = aNewBin;
    };
    std::string const& getBinFolder() const { return mBinFolder; };
  private:
    PathKeeper() : mBinFolder{"./"} {  }
    ~PathKeeper() {  }
    PathKeeper(PathKeeper const&) = delete;
    PathKeeper& operator= (PathKeeper const&) = delete;
    std::string mBinFolder;
};
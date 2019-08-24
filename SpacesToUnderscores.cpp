#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void eraseDotFiles ( std::vector <std::string> & folder )
{
  const char * dot = ".";
  std::cout << dot[0] << "\n";
  for ( auto it = folder.begin(); it != folder.end(); ++it )
  {
    const char * dummy = (*it).c_str();
    if ( dummy[0] == dot[0] )
    {
      //std::cout << "Jsem uzitecnej\n";
      folder.erase( it );
    }
  }
}

int main(void)
{
  const char * dot = ".";
  std::cout << "Are you sure you want to replace all spaces to underscores in the current folder? write 'yes' if so, otherwise anything else.\n";
  std::string safety;
  if ( !(std::cin >> safety) || !(safety == "yes") )
  {
    std::cout << "You just saved your ass homie.\n";
    return 1;
  }
  fs::path path = fs::current_path();
  std::vector <std::string> originalFileNames;
  std::vector <std::string> fileNames;

  for ( auto & entry : fs::directory_iterator(path) )
  {
    std::cout << entry.path().filename() << "\n";
    const char * dummy = entry.path().filename().c_str();
    if ( dummy[0] == dot[0] )
    {
      continue;
    }
    fileNames.emplace_back( entry.path().filename() );
    originalFileNames.emplace_back( entry.path().filename() );
  }

std::cout << "\n\n\n";
  eraseDotFiles(originalFileNames);
  eraseDotFiles(fileNames);

  auto it = fileNames.begin();
  while ( it != fileNames.end() )
  {
    while ( ( (*it).find(" ") != std::string::npos ) || ( (*it).find("%20") != std::string::npos ) )
    {
      if ( (*it).find(" ") != std::string::npos )
      {
        size_t idx = (*it).find(" ");
        (*it).replace( idx, 1, "_" );
      }
      else if ( (*it).find("%20") != std::string::npos )
      {
        size_t idx = (*it).find("%20");
        (*it).replace( idx, 3, "_" );
      }
    }

    ++it;
  }
  auto itF = fileNames.begin();
  auto itO = originalFileNames.begin();
  for ( itF = fileNames.begin(); itF != fileNames.end(); ++itO, ++itF )
  {
    fs::rename( fs::current_path()/ *itO, fs::current_path()/ *itF );
    std::cout << *itF << "\n";
  }

  return 0;
}
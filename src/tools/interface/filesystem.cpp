/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include <iostream>
#include <boost/filesystem.hpp>

#include "tools/interface/filesystem.hpp"
#include "algorithm/string/starts_with.h"
#include "algorithm/string/split.h"

namespace filesystem
{

void makeDir(const std::string &rootPath, const std::string &newDirectory)
{
  
  const std::string fullpath = rootPath + "/" + newDirectory ;
  const boost::filesystem::path directory( fullpath ) ;
  
  try {
    boost::filesystem::create_directory( directory ) ;
  } catch (std::exception const& ex) {
    std::cerr << ex.what() << "\n";
    std::cerr << fullpath;
  }
  
  return;
}


directory::directory(const std::string &workingDirectory_):
  workingDirectory( workingDirectory_ ), myDirectory( workingDirectory_ ){}

directory::~directory(void){}
void directory::mkdir(const std::string &newDirectory) const
{
  if ( ! boost::filesystem::is_directory( abs( newDirectory ) ) )
  {

    makeDir( workingDirectory , newDirectory ) ;
  }


}

std::string directory::working_directory_string() const {
  using std::string;
  using std::vector;
  
  using algorithm::string::split;
  
  const string& delimiter = "/";
  const vector< string > folders =  split( pwd(), delimiter  ) ;
  
  const string last = folders.back();
  
  const string working_folder_only = !last.empty() ? folders.rbegin()[0]
                                                   : folders.rbegin()[1] ;


  return working_folder_only;
}

bool directory::working_directory_starts_with( const std::string& check ) const {
  
  BOOST_ASSERT( true ) ;
  using std::string;
  using std::vector;
  
  using algorithm::string::starts_with;

  const string wk_folder = working_directory_string() ;
  const bool pass = starts_with( wk_folder, check ) ;
  return pass;
}

std::string directory::pwd(void) const
{
  return workingDirectory;
}

std::string directory::abs( const std::string &relativePath) const
{
  return workingDirectory + "/" + relativePath;
}

directory directory::parent_path() const {

  boost::filesystem::path parentPath = myDirectory.parent_path();
  return directory( parentPath.string() ) ;
}


std::string directory::working_directory() const {
  using std::string;
  
  const string working_path = pwd();
  
  
  
  const string myWorkingDirectory( "fix_this" ) ;
  return myWorkingDirectory ;
}

std::vector<directory> directory::ls() const
{
  return ::filesystem::ls( pwd() ) ;
}

std::vector< directory > ls( const std::string &path_in )
{
  using namespace boost::filesystem;
  path p ( path_in );
  std::vector< directory > output;

  size_t dir_count = 0;
  size_t file_count = 0;
  size_t other_count = 0;

  if (!exists(p))
  {
    std::cout << "\nNot found: " << path_in << std::endl;
    return output;
  }

  if( is_directory( p ) )
  {
    directory_iterator end_iter;

    for ( directory_iterator dir_itr(p) ;  dir_itr != end_iter; ++dir_itr )
    {
      try
      {
        if( is_directory( dir_itr->status() ) )
        {
          ++dir_count;
          //std::cout << dir_itr->path().filename() << " [directory]\n";
          const boost::filesystem::path temp_dir( dir_itr->path() ) ;
          const directory mytemp ( temp_dir.string() ) ;
          output.push_back( mytemp ) ;
        }
        else if ( is_regular_file( dir_itr->status() ) )
        {
          ++file_count;
          //std::cout << dir_itr->path().filename() << "\n";
        }
        else
        {
          ++other_count;
          //std::cout << dir_itr->path().filename() << " [other]\n";
        }
      }
      catch (const boost::filesystem::filesystem_error& ex)
      {
        std::cerr << ex.what() << "\n";
      }
    }
  }
  else // must be a file
  {
    std::cout << "\nFound: " << p << "\n";
  }

  return output;
}

}

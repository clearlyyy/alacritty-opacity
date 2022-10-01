//main.cpp
//
#include "includes.h"
#include "opacity.cpp"
  

int setOpacity(char* opacity)
{
  float newOpacity;

  std::stringstream ss(opacity);
  ss >> newOpacity;

  newOpacity = newOpacity / 100;

  std::string loc;
  std::ifstream locFile;
  locFile.open("loc.opacity");
  if (locFile.is_open())
  {
    locFile >> loc;
  }
  else { 
    printf("Error in setOpacity() Function! cannot open 'loc.opacity' file! :(");
    return 1;
  }
  std::string line;
  std::ifstream termFile;
  termFile.open(loc);
  int offset;
  int counter = 0;
  int lineNumber;
  if (termFile.is_open())
  {
    while (!termFile.eof())
    {
      counter++;
      getline(termFile,line);
      if ((offset = line.find(std::string("opacity:"), 0)) != std::string::npos) {
        //std::cout << "on line: " << counter << std::endl;
        //std::cout << line << std::endl;
        lineNumber = counter;
      } 
    }
  }
  else {
    printf("Error in setOpacity() Function! cannot find alacritty.yml file :(\n");
    printf("Your -loc file location may be incorrect! try -help");
    return 1;
  }
  //std::cout << counter << std::endl;

  std::fstream filein;
  std::ofstream write_file;
  
  filein.open(loc);
  if (filein.fail())
    std::cout << "Error in setOpacity() function! cannot open allacritty.yml file :(\n";
  
  std::vector<std::string> lines;
  std::string line2;
  
  while (getline(filein, line2))
  {
    lines.push_back(line2);
  }
  filein.close();
  
  if (lineNumber > lines.size())
  {
    std::cout << "Error in setOpacity(), int lineNumber too big, there is not enough lines in the file :(\n";
    std::cout << loc << " Only has " << lines.size() << " Lines\n";
    std::cout << "lineNumber = " << lineNumber << "Which is too big!";
  }

  write_file.open(loc);

  if (write_file.fail()) {
    std::cout << "Error in setOpacity, couldn't open alacritty.yml file :(\n";
    return 1;
  }
  std::string strOpacity = std::to_string(newOpacity);

  lineNumber--;
  for (int i = 0; i < lines.size(); i++)
  {
    if (i != lineNumber)
      write_file << lines[i] << std::endl;
    else
      write_file << "  opacity: " << strOpacity  << std::endl;
  }
  
  write_file.close();
  return 1;
  //set line with new opacity;
} 

int main(int argc, char** argv)
{
  //std::string location = NULL;
  char* instr = argv[1];
  char* instr2 = argv[2];
  if (strcmp(instr, "-help") == 0)
  {
    printf("---------------------------------Help Page---------------------------------\n"); 
    printf("To Set File Location, use -loc as an argument, and put the location of your alacritty.yml file.\n");
    printf("To Set Opacity, simply put a number between 0-100 as an argument\n");
    printf("\nExample: opacity -loc ~/home/alacritty/alacritty.yml (Sets location of alacritty.yml file)\n");
    printf("Example 2: opacity 58 (Sets terminal opacity to 58)                                              ");
  }
   
  else if (strcmp(instr, "-loc") == 0)
  {
    std::ofstream fw("loc.opacity", std::ofstream::out);
    if (fw.is_open())
    {
     fw << std::string(instr2);
     fw.close();
    }
    else { printf("Error! Cannot open loc.opacity file, unable to save location!"); return 1; }
  }
  else
    setOpacity(instr);

}



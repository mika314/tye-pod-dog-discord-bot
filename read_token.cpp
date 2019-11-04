#include "read_token.hpp"
#include <fstream>
#include <iostream>

std::string readTokenFile(const std::string &tokenFilePath)
{
  std::ifstream tokenFile;
  tokenFile.open(tokenFilePath);

  std::string token;

  if (!tokenFile.is_open())
  {
    std::cerr << "CRITICAL: There is no such file as " + tokenFilePath +
                     "! Copy the example login.dat to make one.\n";
    exit(1);
  }
  std::getline(tokenFile, token);
  std::cout << "Retrieved token.\n\n";

  return token;
}

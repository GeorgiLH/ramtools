#include "ramcore/RAMNTupleView.h"
#include <iostream>
#include <stdio.h>
#include <Rtypes.h>
namespace {
int checkFlagIndex(int argc, char *argv[], const std::string &flag)
{

   for (int i = 0; i < argc; ++i) {
      if (argv[i] == flag) {
         return i;
      }
   }

   return -1;
}

} // namespace

int main(int argc, char *argv[])
{
   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " <file.root> [rname:start-end]\n";
      std::cerr << "Example: " << argv[0] << " output.root chr1:1000-2000\n";
      return 1;
   }

   const char *file = argv[1];
   const char *region_str = (argc > 2) ? argv[2] : "";
   RAMNTupleViewOpts opts;
   int iWriteFlag = checkFlagIndex(argc, argv, "-o");
   if (iWriteFlag > 0) {
      opts.fWriteFile = true;
      if (iWriteFlag < argc - 1) {
         opts.filenameout = argv[iWriteFlag + 1];
      }
   }

   Long64_t read_count = ramntupleview(file, region_str, opts);

   printf("Found %lld records in region %s\n", read_count, region_str);

   return 0;
}

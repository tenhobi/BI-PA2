#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>
#include <queue>
using namespace std;

const unsigned int ENDIAN_LITTLE   =  0x4949;
const unsigned int ENDIAN_BIG      =  0x4d4d;

#endif /* __PROGTEST__ */

bool rotateImage ( const char  * srcFileName,
                   const char  * dstFileName,
                   int           angle,
                   unsigned int  byteOrder )
{
  // todo
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
  // DIY
}

int main ( void )
{
  assert (  rotateImage ( "input_00.img", "output_00.img", 0, ENDIAN_LITTLE )
         && identicalFiles ( "output_00.img", "ref_00.img" ) );

  assert (  rotateImage ( "input_01.img", "output_01.img", 90, ENDIAN_LITTLE )
         && identicalFiles ( "output_01.img", "ref_01.img" ) );

  assert (  rotateImage ( "input_02.img", "output_02.img", 540, ENDIAN_LITTLE )
         && identicalFiles ( "output_02.img", "ref_02.img" ) );

  assert (  rotateImage ( "input_03.img", "output_03.img", -900450, ENDIAN_LITTLE )
         && identicalFiles ( "output_03.img", "ref_03.img" ) );

  assert (  rotateImage ( "input_04.img", "output_04.img", 90, ENDIAN_LITTLE )
         && identicalFiles ( "output_04.img", "ref_04.img" ) );

  assert (  rotateImage ( "input_05.img", "output_05.img", 270, ENDIAN_LITTLE )
         && identicalFiles ( "output_05.img", "ref_05.img" ) );

  assert (  rotateImage ( "input_06.img", "output_06.img", 90, ENDIAN_LITTLE )
         && identicalFiles ( "output_06.img", "ref_06.img" ) );

  assert (  rotateImage ( "input_07.img", "output_07.img", 270, ENDIAN_LITTLE )
         && identicalFiles ( "output_07.img", "ref_07.img" ) );

  assert ( ! rotateImage ( "input_08.img", "output_08.img", 270, ENDIAN_LITTLE ) );

  assert ( ! rotateImage ( "input_09.img", "output_09.img", -275, ENDIAN_LITTLE ) );

  // extra inputs (optional & bonus tests)
  assert ( rotateImage ( "extra_input_00.img", "extra_out_00.img", 90, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
  assert ( rotateImage ( "extra_input_01.img", "extra_out_01.img", 90, ENDIAN_BIG )
           && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
  assert ( rotateImage ( "extra_input_02.img", "extra_out_02.img", 180, ENDIAN_BIG )
           && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
  assert ( rotateImage ( "extra_input_03.img", "extra_out_03.img", 270, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
  assert ( rotateImage ( "extra_input_04.img", "extra_out_04.img", 90, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
  assert ( rotateImage ( "extra_input_05.img", "extra_out_05.img", 270, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
  assert ( rotateImage ( "extra_input_06.img", "extra_out_06.img", 180, ENDIAN_BIG )
           && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
  assert ( rotateImage ( "extra_input_07.img", "extra_out_07.img", 0, ENDIAN_BIG )
           && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
  assert ( rotateImage ( "extra_input_08.img", "extra_out_08.img", 90, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
  assert ( rotateImage ( "extra_input_09.img", "extra_out_09.img", 270, ENDIAN_LITTLE )
           && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
  assert ( rotateImage ( "extra_input_10.img", "extra_out_10.img", 180, ENDIAN_BIG )
           && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
  assert ( rotateImage ( "extra_input_11.img", "extra_out_11.img", 0, ENDIAN_BIG )
           && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
  return 0;
}
#endif /* __PROGTEST__ */

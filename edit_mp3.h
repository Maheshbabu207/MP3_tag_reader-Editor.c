#ifndef EDIT_MP3_H
#define EDIT_MP3_H

#include "types.h"      //Contains User-defined Data Types.

/*
 * Structure to store information required for storing the Updated Fram Content details
 * Information abouth the Source and Temporary MP3 files
 */

typedef struct mp3_TagData
{
    /* Source MP3 file Info */
    FILE* fptr_mp3;

	/* Temporary MP3 file Info */
    FILE* fptr_temp;

	/* Updated value Info passed in the Command Line */
    char frame_Id [5];
    char frame_Id_value [100];
    uint frame_Id_size;

} mp3_tag_info;

/* Editing MP3 details Function Prototype */

/* Perform Validation of the Arguments passed and store in the Structure */
Status validate_mp3_file_args (char* argv[], mp3_tag_info* mp3tagData);

/* Perform the Editing Tag details Operation */
Status edit_mp3_tag (char* argv[], mp3_tag_info* mp3tagData);

/* Copy the Frame Contents from the Source to Temporary MP3 file */
Status copy_data (mp3_tag_info* mp3tagData, char flag);

/* Copy the contents after the Frames have been copied from Source to Temporary MP3 file */
Status copy_remaining_data (mp3_tag_info* mp3tagData);

/* Copy the complete Data from the Temporary to Source MP3 file */
Status copy_back_to_src (mp3_tag_info* mp3tagData);

#endif
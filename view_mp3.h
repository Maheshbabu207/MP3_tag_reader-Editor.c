#ifndef VIEW_MP3_H
#define VIEW_MP3_H

#include "types.h"

typedef struct mp3_tag
{
    
    FILE* fptr_mp3;
    char frame_Id [4];

    char* title_tag;
    uint title_tag_size;

    char* artist_tag;
    uint artist_tag_size;

    
    char* album_tag;
    uint album_tag_size;

    char* year;
    uint year_size;

    
    char* content_type;
    uint content_type_size;

   
    char* comments;
    uint comment_size;

} MP3_Tag_Info;



/* Check Operation type */
OperationType check_CLA(char* argv[]);

/* Perform Validation of the Arguments passed and store in the Structure */
Status validate_mp3_file (char *argv[], MP3_Tag_Info *mp3tagInfo);

/* Perform the Viewing Tag details Operation */
Status view_mp3_tag (char* argv[], MP3_Tag_Info *mp3tagInfo);

/* Common function to display the various Frame contents of the MP3 file */
Status get_and_display_data (const char* str_frame, const char* str_Id, char* frame_Id, uint* tag_size, char* tag, FILE* fptr);

#endif
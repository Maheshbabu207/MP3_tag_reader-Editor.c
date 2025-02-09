#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "view_mp3.h"


OperationType check_CLA(char* argv[])
{
    if (strncmp (argv [1], "-v", 2) == 0)
    {
        return view_tag;
    }
    else if (strncmp (argv [1], "-e", 2) == 0)
    {
        return edit_tag;
    }
    else if (strncmp (argv [1], "--help", 6) == 0)
    {
        return help;
    }
    else
    {
        return unsupported;
    }
}



Status validate_mp3_file (char* argv[], MP3_Tag_Info* mp3tagInfo)
{
    if (argv [2] == NULL)		
    {
        printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
        return FAILURE;
    }
    else
    {
        mp3tagInfo->fptr_mp3 = fopen (argv [2], "r");		
        if (mp3tagInfo->fptr_mp3 != NULL)
        {
            char str[3];
            fread (str, 1, 3, mp3tagInfo->fptr_mp3);		
            if ((strncmp (str, "ID3", 3)) == 0)				
            {
                printf ("                             Version ID: v2.3                         \n");
                printf ("-----------------------------------------------------------------------------------\n");
            }
            else		
            {
                printf ("ERROR: The file Signature is not matching with that of a '.mp3' file.\n");
                printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
                return FAILURE;
            }
        }
        else		
        {
            printf ("ERROR: Unable to Open the %s file.\n", argv [2]);
            printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
            return FAILURE;
        }

        fclose (mp3tagInfo->fptr_mp3);						
    }

    return SUCCESS;
}



Status view_mp3_tag(char* argv[], MP3_Tag_Info* mp3tagInfo)
{
    mp3tagInfo->fptr_mp3 = fopen (argv [2], "r");		
    fseek (mp3tagInfo->fptr_mp3, 10L, SEEK_SET);		
	Status ret;

	
    ret = get_and_display_data ("Title: ", "TIT2", mp3tagInfo->frame_Id, &mp3tagInfo->title_tag_size, mp3tagInfo->title_tag, mp3tagInfo->fptr_mp3);
    if (ret == FAILURE)		
    {
        printf ("ERROR: Title Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }


    ret = get_and_display_data ("Artist: ", "TPE1", mp3tagInfo->frame_Id, &mp3tagInfo->artist_tag_size, mp3tagInfo->artist_tag, mp3tagInfo->fptr_mp3);
    if (ret == FAILURE)		
    {
        printf ("ERROR: Artist Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

    ret = get_and_display_data ("Album: ", "TALB", mp3tagInfo->frame_Id, &mp3tagInfo->album_tag_size, mp3tagInfo->album_tag, mp3tagInfo->fptr_mp3);
    if (ret == FAILURE)		
    {
        printf ("ERROR: Album Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

	
    ret = get_and_display_data ("Year: ", "TYER", mp3tagInfo->frame_Id, &mp3tagInfo->year_size, mp3tagInfo->year, mp3tagInfo->fptr_mp3);
    if (ret == FAILURE)		
    {
        printf ("ERROR: Year Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }


    ret = get_and_display_data ("Content: ", "TCON", mp3tagInfo->frame_Id, &mp3tagInfo->content_type_size, mp3tagInfo->content_type, mp3tagInfo->fptr_mp3);
    if (ret == FAILURE)		
    {
        printf ("ERROR: Content Type Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }


    ret = get_and_display_data ("Comments: ", "COMM", mp3tagInfo->frame_Id, &mp3tagInfo->comment_size, mp3tagInfo->comments, mp3tagInfo->fptr_mp3);
    if (ret == FAILURE)		
    {
        printf ("ERROR: Content Type Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

    printf ("-----------------------------------------------------------\n");
    fclose (mp3tagInfo->fptr_mp3);				

    
    return SUCCESS;
}



Status get_and_display_data (const char* str_frame, const char* str_Id, char* frame_Id, uint* tag_size, char* tag, FILE* fptr)
{
    int count;
    count = fread (frame_Id, 1, 4, fptr);				
    if (count < 4)										
    {
        printf ("ERROR: Unable to read from the MP3 file.\n");
        return FAILURE;
    }
    else
    {
        if ((strncmp (frame_Id, str_Id, 4)) == 0)		
        {
            count = fread (tag_size, 4, 1, fptr);		
            
           
            if (count < 1)								
            {
                printf ("ERROR: Unable to read from the MP3 file.\n");
                return FAILURE;
            }
            else										
            {
                char* pos = (char*) tag_size;
                for (int i = 0; i < ((sizeof (uint)) / 2); i++)
                {
                    pos [i] = pos [i] ^ pos [(sizeof (uint)) - i - 1];
                    pos [(sizeof (uint)) - i - 1] = pos [i] ^ pos [(sizeof (uint)) - i - 1];
                    pos [i] = pos [i] ^ pos [(sizeof (uint)) - i - 1];
                }
                tag = (char*) malloc (((*tag_size) * sizeof (char)));		

                fseek (fptr, 3L, SEEK_CUR);		

				
                count = fread (tag, 1, (*tag_size - 1), fptr);		
                if (count < (*tag_size - 1))						
                {
                    printf ("ERROR: Unable to read from the MP3 file.\n");
                    return FAILURE;
                }
                else
                {
                    tag [*tag_size - 1] = '\0';						
                 
                    printf ("%-10s%s.\n", str_frame, tag);			
                }
            }
        }
        else		
        {
            printf ("ERROR: %s Frame ID not found.\n", str_Id);
            return FAILURE;
        }
    }

    free (tag);			
    tag = NULL;
    return SUCCESS;
}
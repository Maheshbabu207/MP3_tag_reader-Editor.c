/*Name:Maheshbabu.D
Batch:24024C
Project:MP3_TAG_READER_AND EDITOR
*/

#include <stdio.h>
#include "types.h"
#include "view_mp3.h"
#include "edit_mp3.h"

int main(int argc, char* argv[])
{
    MP3_Tag_Info mp3tagInfo;
    mp3_tag_info mp3tagData;

    if (argc < 2)		
    {
        printf ("ERROR: Incorrect format of Command Line Arguments.\n");
        printf ("INFO: Use \"./mp3_tag_reader --help\" for Help menu.\n");
    }
    else
    {
        OperationType ret = check_CLA(argv);

        if (ret == view_tag)
        {
            printf ("-----------------------------------------------------------------------------------\n");
            printf("----------------------------> Selected View Details <-------------------------------\n");
            printf ("-----------------------------------------------------------------------------------\n");
            printf ("                             MP3 Tag Reader and Editor                             \n");
            printf ("-----------------------------------------------------------------------------------\n");
            Status ret1 = validate_mp3_file (argv, &mp3tagInfo);		//To validate all the arguments passed in Command Line.
            if (ret1 == SUCCESS)			//If validation is successful, proceed with the Viewing process.
            {
                Status ret2 = view_mp3_tag (argv, &mp3tagInfo);						//To execute the Viewing process of the MP3 Tag.
                if (ret2 == SUCCESS)		//If the Viewing process is successfully executed, print a confirmation message.
                {
                    printf ("-------------> Details Displayed Successfully <------------\n");
                    printf ("-----------------------------------------------------------\n");
                }
            }
        }
        else if (ret == edit_tag)			//If the return value from the function is to perform Editing the MP3 Tag, proceed for Validation and Editing process.
        {
            printf ("-----------------------------------------------------------------------------------\n");
            printf("----------------------------> Selected Edit Details <-------------------------------\n");
            printf ("-----------------------------------------------------------------------------------\n");
            printf ("                             MP3 Tag Reader and Editor                             \n");
            printf ("-----------------------------------------------------------------------------------\n");
            Status ret1 = validate_mp3_file_args(argv, &mp3tagData);	//To validate all the arguments passed in Command Line.
            if (ret1 == SUCCESS)			//If validation is successful, proceed with the Editing process.
            {
                Status ret2 = edit_mp3_tag (argv, &mp3tagData);						//To execute the Editing process of the MP3 Tag.
                if (ret2 == SUCCESS)		//If the Editing process is successfully executed, print a confirmation message.
                {
                    printf ("-------------> Details Displayed Successfully <------------\n");
                    printf ("-----------------------------------------------------------\n");
                    //Call the view_tag function to display the Updated content.
                }
            }
        }
        else if (ret == help)			//If the return value from the function is to show the Help Menu, display all the details regarding the usage of MP3 Tag Reader & Editor.
        {
            printf ("-----------------------> Help Menu <----------------------------------\n");
            printf("1. -v -> To View mp3_file Contents\n");
            printf("2. -e -> To Edit mp3_file Contents\n");
            printf("      2.1 -t -> to edit song title\n");
            printf("      2.2 -a -> to edit Artist name\n");
            printf("      2.3 -A -> to edit Album name\n");
            printf("      2.4 -y -> to edit year\n");
            printf("      2.5 -m -> to edit content\n");
            printf("      2.6 -c -> to edit comment\n");
        }
        else if (ret == unsupported)	//If the return value from the function is other than to perform View/Edit/Help, print an error message.
        {
            printf ("ERROR: Unsupported Operation.\n");
            printf ("INFO: Use \"./mp3_tag_reader --help\" for Help menu.\n");
        }
    }

    return 0;
}
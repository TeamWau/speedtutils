Information for Devs
===========

This file provides some basic information and style guidelines intended for programmers on the speedutils project.
To keep some uniformity, we need to have some standard code styling.

For standard C code, please follow this structure (or some variation; not putting an extra space between parentheses and their contents is fine):

    /* Adds arg1 with arg2 */
    int function( int arg1, int arg2 ) {
        int result = arg1 + arg2;
        printf( "arg1(%d) and arg2(%d) added successfully!\n", arg1, arg2 );

        return result;
    }

    int main() {
        // this calls function() with the arguments 1 and 2 and stores their value in "i"
        int i = function( 1, 2 );
        printf( "The result of adding 1 and 2: %d\n", i );

        return 0;
    }

Please make sure the following criteria are met:

1. You use four spaces to indent and no tab characters
2. Try to keep a close look to the above snippet.




Return Values
---------

`main()` should return the following values for each of these conditions:

* `0` - successful completion of program
* `1` - minor issue (not invoking with commands if the program requires it, for example)
* `2` - major issue (file not found if trying to work with a file)

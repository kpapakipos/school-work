# Name: Keegan Papakipos
# Date: Tuesday 2:15
# Title: Lab1 – Unix/Linux Commands and Basic Shell Programming
# Description: This script is the third and final version of the script. It prints out information about this location in the file system, your user, and path. Then if your username is keeganpapakipos (which mine is), it will calculate the areas of arbitrarily-sized circles.

#Sample shell programs for Lab assignment 
#!/bin/sh
echo  Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "kpapakip" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1
fi

response="Yes"
while [ $response != "No" ]
do
        echo "Enter radius of circle: "
        read radius
        area=`echo "3.1416 * $radius * $radius" | bc`
        echo "The area of the circle is $area"
        
        echo "Would you like to repeat for another circle [Yes/No]?"
        read response
        
done

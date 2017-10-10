# PCBHelper
Helps when designing and ordering parts for circuit boards in version 5 of Eagle's PCB CAD program (i.e., 5.11.0).

This application was quickly written years ago before I knew more about using SQL in applications. 
It is therefore quite inelegant and not remotely efficient.

The application builds a database of Digikey part numbers for parts used in creating a PCB.

The user can use the application during the design process to make decisions about footprint 
sizes (e.g., "Do I normally use a 0402 or a 0603 for a 1uF capacitor?").

Most importantly, when the design of the PCB is done, the user can take the output Eagle's 
"bom.ulp" script to automatically scrape the data from the database and save a comma-delimited
output file that can be copy/pasted into Digikey's bom import page. This is the sole reason the application was 
made and saves hours of tedious error-prone work for every project. Instead of manually finding parts on Digikey's
website for each part on your board, simply run the Export BOM function of the application and you're done.

For parts on the board that have multiple matches in the database (e.g., 16V and 25V tolerant capacitors), the
application notes this in the output file, as it does for parts that need information to be added to the 
database (e.g., you put a regulator on the board, but do not have a matching regulator in the database).

TODO (someday or by someone else): 
  Remove the C++ objects used to contain the database information 
and make use of multiple SQL calls to refine output as the user selects options throughout the GUI.

  Place the output of the dropdown boxes in a sorted order.
  
  Create and use a config file that saves the preferred location of the user's part database so the user 
    doesn't need to locate the db file every time the user opens the application.
    
  Add a method of removing parts from the database. No one wants to do this from the command line using sqlite3.
  

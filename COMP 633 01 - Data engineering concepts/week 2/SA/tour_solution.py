"""
This is a stub for COMP63301 Coursework 02.
Do not edit or delete any lines given in this file that are marked with a "(s)".
(you can move them to different lines as long as you do not change the overall structure)

Only the SQLite3 package should be imported for testing purposes; refrain from importing any other packages.

Use the test zone at the bottom of this stub to test your code locally.

Place your code below the comments marked "#Your code here" and before the next method.

Each method is documented to explain what functionality is to be placed within.

NOTE: You can create as many more methods as you need. However, you need to add 
self as a parameter of the new method and to call it with the prefix self.name 

EXAMPLE:

    def clean(self,result):
        cleaned = [item[0] for item in result]
        return cleaned

"""

class Tours:#(s)
 
    # ---Section 1 --- #
 
    #(Question 1)
    def replace_NaN_with_stop(self,conn):#(s)
        """
                a.	Identify all missing values in the end_location_name column, 
                        saving the trip_id associated with the first 10 rows with a missing value for end_location_name.

                b.	Replace each missing entry using each of the three strategies described above, 
                        one-at-a-time. You will need to restore each of the rows that had the value of end_location_name filled to its state, 
                        before its end_location_name value was filled (i.e., a missing end_location_name), before applying the next strategy.

                c.	For each strategy and for each of the first 10 replacements, 
                        compute and return the total number of occurrences of the associated, new, pair <start_location_name, end_location_name>.
                    
                Returns: List: [('trip_id', 'start_location_name', 'end_location_name', 'pair_count'), (263511, '80 Whitworth BM, Albuquerque, NY 87888, ILD', '898 Mountain Rd NW, Albuquerque, NM 87104, USA', 3) , (333333, '71 Whitworth NW, Albuquerque, NM 16161, USA', 'Stop St.', 3), .....]
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass

    #(Question 2)
    def replace_NaN_with_start(self,conn):#(s)
        """
                a.	Identify all missing values in the start_location_name column, saving the trip_id associated with the first 6 rows with a missing value for start_location_name.

                b.	Replace each missing entry with the most frequent start_location_name value in the table.

                c.	For each of the first 6 replacements, compute and return the total number of occurrences of the associated, new, pair <start_location_name, end_location_name>
        
                Returns: List: [['trip_id', 'start_location_name', 'end_location_name', 'pair_count'], (555555, '80 Whitworth BM, Albuquerque, NY 87888, ILD', '898 Mountain Rd NW, Albuquerque, NM 87104, USA', 3) , (333333, '71 Whitworth NW, Albuquerque, NM 123123, USA', 'Stop St.', 3), .....]
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass

    #(Question 3)
    def column_name_change(self,conn):#(s)
        """
            Standardise the naming convention of the DURATION column to align with typical lowercase formatting used in data schemas,
            by having this column name replaced with duration. Once the standardisation is performed, return the new column name and the first 5 values in this column.
          
            Returns: List: (['duration'], ['h:mm:ss', 'h:mm:ss', 'h:mm:ss', 'h:mm:ss', 'h:mm:ss'])
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass
        

    #(Question 4)
    def normalize(self,conn):#(s)
        """
            Normalize the values in the month column so that all entries are in lowercase (i.e., june), regardless of their original format.
            Once the normalisation is performed, return, for only the following columns, the first 5 data values. 
            Note that the column names should appear in the results: month, trip_id, duration. 
            
            Returns: List: (['month', 'trip_id', 'duration'], [('month', 1613335, 'h:mm:ss'), ('month', 1613639, 'h:mm:ss'), ('month', 1613708, 'h:mm:ss'), ('month', 1613867, 'h:mm:ss'), ('month', 1636714, 'h:mm:ss')])

        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass
      
    #(Question 5)
    def trip_duration(self,conn):#(s)
        """
            For entries in the duration column that are missing, derive the appropriate values using the started_at and ended_at columns. 
            Ensure these columns are in a format that supports datetime operations. Once the missing values are filled with the derived values, 
            return count of Nan values in column duration, as well as the data values in columns trip_id and duration for ONLY the rows with 
            the following trip_id values: 1821126, 1821158, 1821204, 1821289, 2047623. Make sure that the column names appear in the results.
         
            Returns: List: (NaN_count, ['trip_id', 'duration'], [(1821126, 'h:mm:ss'), (1821158, 'h:mm:ss'), (1821204, 'h:mm:ss'), (1821289, 'h:mm:ss'), (2047623, 'h:mm:ss')])
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass

    #(Question 6)
    def shortest_trip(self,conn):#(s)
        """
            Return the shortest trip duration in the database and the number of distinct 
                <start_location_name, end_location_name> pair(s) associated with this duration value. 

            Returns: List: [('h:mm:ss', distinct_pairs_number)]
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass
        

    #(Question 7)
    def median_duration_trip(self, conn):#(s)
        """
              Return the median trip duration in the database and the number of distinct  <start_location_name, end_location_name> pair(s) associated with this duration value.

            Returns: List: [('h:mm:ss', distinct_pairs_number)]
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass
 
    #(Question 8)
    def trips_distance_in_miles(self,conn):#(s)
        """

            Using the Haversine formula, based on coordinates in table geocode, calculate the distance in miles between <start_location_name, end_location_name> of the following trip_ids:
            1637299, 1640777, 1652952
          
            Returns: List: [(1637299, distance_in_miles), (1640777, distance_in_miles), (1652952, distance_in_miles)]   
        """
        cursor = conn.cursor()#(s)
        #Your code here
        pass

# ---Test Zone --- #

"""
Remove the comments below to test your solution locally. Once the solution is finalised, reapply the comments as they are currently.
"""

# import sqlite3

# if __name__ == '__main__':

#     #You can place any ad-hoc testing here 
#     conn = sqlite3.connect("coursework2.db")
#     my_instance = Tours()
#     print("Question 1")
#     print(my_instance.replace_NaN_with_stop(conn))
#     print("Question 2")
#     print(my_instance.replace_NaN_with_start(conn))
#     print("Question 3")
#     print(my_instance.column_name_change(conn))
#     print("Question 4")
#     print(my_instance.normalize(conn))
#     print("Question 5")
#     print(my_instance.trip_duration(conn))
#     print("Question 6")
#     print(my_instance.shortest_trip(conn))
#     print("Question 7")
#     print(my_instance.median_duration_trip(conn))
#     print("Question 8")
#     print(my_instance.trips_distance_in_miles(conn))
#     conn.close()  # Close the connection when done



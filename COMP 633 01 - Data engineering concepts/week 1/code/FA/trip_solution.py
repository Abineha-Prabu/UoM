"""
This is a stub for COMP63301 Coursework 01.
Do not edit or delete any lines given in this file that are marked with a "(s)".
(you can move them to different lines as long as you do not change the overall structure)

Place your code below the comments marked "#Your code here" and before the for that method.

Each method is documented to explain what work is to be placed within it.

NOTE: You can create as many more methods as you need. However, you need to add 
self as a parameter of the new method and to call it with the prefix self.name 

EXAMPLE:

    def clean(self,result):
        cleaned = [item[0] for item in result]
        return cleaned

"""

class Trip:#(s)

    # ---Section 1 --- #
 
    #(Question 1)
    def replace_NaN_with_stop(self,df):#(s)
        """
            Inspect the end_location_name column and ensure that missing entries are replaced with the following, meaningful, placeholder value: Stop St.
            Once the replacements are performed, return all occurrences of value 'Stop St.' in column end_location_name. 
            
            Returns: int
        """
       #Your code here
        df["end_location_name"] = df["end_location_name"].fillna(value = "Stop St.")
        num = (df["end_location_name"] == "Stop St.").sum()
        return int(num)

        

    #(Question 2)
    def replace_NaN_with_start(self,df):#(s)
        """
            Address missing values in the start_location_name column by substituting them with the following, meaningful, placeholder value: Start St.
            Once the replacements are performed, return all occurrences of value 'Start St.' in column start_location_name.
            
            Returns: int  
        """
        df["start_location_name"] = df["start_location_name"].fillna(value = "Start St.")
        num = (df["start_location_name"] == "Start St.").sum()
        return num

    #(Question 3)
    def trip_duration(self,df):#(s)
        """
            For entries in the duration column that are missing, derive the appropriate values using the started_at and ended_at columns. 
            Ensure these columns are in a format that supports datetime operations. Once the missing values are filled with the derived values, 
            return count of Nan values in column duration, as well as the data values in columns trip_id and duration for ONLY the rows with 
            the following trip_id values: 1821126, 1821158, 1821204, 1821289, 2047623. Make sure that the column names appear in the results.
         
            Returns: List: (NaN_count, ['trip_id', 'duration'], [(1821126, 'hh:mm:ss'), (1821158, 'hh:mm:ss'), (1821204, 'hh:mm:ss'), (1821289, 'hh:mm:ss'), (2047623, 'hh:mm:ss')])
        """
        #Your code here
        df = df.copy()
        df['started_at'] = pd.to_datetime(df['started_at'])
        df['ended_at'] = pd.to_datetime(df['ended_at'])
    
        mask_isna = df['DURATION'].isna()
        df.loc[mask_isna, 'DURATION'] = df.loc[mask_isna, 'ended_at'] - df.loc[mask_isna, 'started_at']

        def format_duration(td):
            total_seconds = int(td.total_seconds())
            hours = total_seconds // 3600
            minutes = (total_seconds % 3600) // 60
            seconds = total_seconds % 60
            return f"{hours:02d}:{minutes:02d}:{seconds:02d}"
    
        df['DURATION'] = df['DURATION'].apply(lambda x: format_duration(x) if isinstance(x, pd.Timedelta) else x)

        num = int(df['DURATION'].isna().sum())

        target_ids = [1821126, 1821158, 1821204, 1821289, 2047623]
        table = df[df['trip_id'].isin(target_ids)][['trip_id', 'DURATION']]

        table = table.rename(columns={'DURATION': 'duration'})
    
        Table = list(table.itertuples(index=False, name=None))
    
        return [[num], [list(table.columns)] + Table]
        

    #(Question 4)
    def geospatial_data_enrichment(self,df,geo):#(s)
        """
        Return the top-N start streets with counts, enriched with (x,y) from `geo`.

            Returns:
                List[Tuple]: [
                ('street','count','x','y'),
                ('Main St', 42, -2.123, 53.456),
                ...
                ]

        """
        #Your code here
        df = df.copy()
        df['street_only'] = df['start_location_name'].str.split(',').str[0].str.strip()

        top5 = df['start_location_name'].value_counts().head(5).reset_index()
        top5.columns = ['address', 'count']

        top5['street_only'] = top5['address'].str.split(',').str[0].str.strip()

        street_mapping = {
            'Central @ Tingley': 'Central and Tingley'
        }
        top5['street_only'] = top5['street_only'].replace(street_mapping)
    
        table = top5.merge(geo, left_on='street_only', right_on='street', how='left')

        table['x'] = table['x'].round(6)
        table['y'] = table['y'].round(6)

        Table = table[['address', 'count', 'street', 'x', 'y']]

        return [tuple(Table.columns)] + [tuple(x) for x in Table.to_numpy()]

    #(Question 5)
    def summary_duration_trip(self,df):#(s)
        """
            For entries in the duration column that are missing, derive the appropriate values using the started_at and ended_at columns. 
            Ensure these columns are in a format that supports datetime operations. Once the missing values are filled with the derived values, 
            return count of Nan values in column duration, as well as the data values in columns trip_id and duration for ONLY the rows with 
            the following trip_id values: 1821126, 1821158, 1821204, 1821289, 2047623. Make sure that the column names appear in the results.

            Return: List
            [
                ('start_location_name','end_location_name','Minimum','Q1','Median','Q3','Maximum'),
            
                ('A St','B St','12.00 seconds','18.50 seconds','21.00 seconds','25.75 seconds','40.00 seconds'),
                ...
            ]
         
        """
        #Your code here
        df = df.copy()

        def duration_to_seconds(x):
            if isinstance(x, str):
                parts = x.split(':')
                parts = [float(p) for p in parts]
                seconds = 0
                for i, p in enumerate(reversed(parts)):
                    seconds += p * (60 ** i)
                return seconds
            else:
                return float(x)
 
        df['DURATION_seconds'] = df['DURATION'].apply(duration_to_seconds)
 
        grouped = df.groupby(['start_location_name', 'end_location_name'])
        
        summary = []
        for name, group in grouped:
            if len(group) > 1:   
                durations = group['DURATION_seconds']
                min_val = round(durations.min(), 2)
                q1 = round(durations.quantile(0.25), 2)
                median = round(durations.median(), 2)
                q3 = round(durations.quantile(0.75), 2)
                max_val = round(durations.max(), 2)
                summary.append([
                    name[0],            
                    name[1],            
                    f"{min_val:.2f} seconds",
                    f"{q1:.2f} seconds",
                    f"{median:.2f} seconds",
                    f"{q3:.2f} seconds",
                    f"{max_val:.2f} seconds"
                ])
 
        summary = summary[:5]
 
        header = ['start_location_name', 'end_location_name', 'Minimum', 'Q1', 'Median', 'Q3', 'Maximum']
        summary.insert(0, header)
    
        return summary

# ---Test Zone --- #

import pandas as pd

"""
Remove the comments below to test your solution locally. Once the solution is finalised, reapply the comments as they are currently.
"""

# if __name__ == '__main__':

#     #You can place any ad-hoc testing here 
#     my_instance = Trip()
#     df  = pd.read_csv("scooter.csv")
#     geo = pd.read_csv("geocodedstreet.csv")

#     print("Question 1")
#     print(my_instance.replace_NaN_with_stop(df))

#     print("Question 2")
#     print(my_instance.replace_NaN_with_start(df))

#     print("Question 3")
#     print(my_instance.trip_duration(df))

#     print("Question 4")
#     print(my_instance.geospatial_data_enrichment(df,geo))

#     print("Question 5")
#     print(my_instance.summary_duration_trip(df))



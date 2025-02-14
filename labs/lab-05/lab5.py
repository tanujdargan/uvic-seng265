#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import pandas as pd

def main():
    # Read the CSV files
    drivers_df = pd.read_csv('drivers.csv')
    results_df = pd.read_csv('results.csv')
    
    # Filter only the race winners (position = 1)
    winners_df = results_df[results_df['position'] == '1']
    
    # Merge winners with drivers information
    winners_with_info = pd.merge(
        winners_df,
        drivers_df[['driverId', 'nationality']],
        on='driverId'
    )
    
    # Count unique drivers per nationality who won at least one race
    winners_by_country = winners_with_info.groupby('nationality')['driverId'].nunique()
    
    # Sort in descending order and get top 10
    top_10_countries = winners_by_country.sort_values(ascending=False).head(10)
    
    # Print results
    print("\nTop 10 countries with most race winners in F1 history:")
    print("====================================================")
    for country, count in top_10_countries.items():
        print(f"{country}: {count} winners")

if __name__ == "__main__":
    main()
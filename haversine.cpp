// haversine.cpp
//
// Haversine Formula Implementation
//
// The Haversine formula can be used to compute an estimated distance between 
// two points on a sphere. This program provides the ability to compute an 
// estimated distance between two points on the Earth from their respective 
// latitudes and longitudes.
//
// This implementation assumes that the Earth is a perfect sphere, with a 
// radius of 6378 km (3963 miles)

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/math/constants/constants.hpp>

int main(int argc, char* argv[]) {

	// Validate usage
	if (argc != 5) {
		std::cout << "Usage: haversine lat1 lon1 lat2 lon2" << std::endl;
		return -1;
	}

	double lat_1_deg, lon_1_deg, lat_2_deg, lon_2_deg;
	sscanf(argv[1], "%lf", &lat_1_deg);
	sscanf(argv[2], "%lf", &lon_1_deg);
	sscanf(argv[3], "%lf", &lat_2_deg);
	sscanf(argv[4], "%lf", &lon_2_deg);
	
	std::cout << "Calculating distance between ("
			  << std::setprecision(9) << lat_1_deg << "," 
			  << std::setprecision(9) << lon_1_deg << ")" << " and ("
			  << std::setprecision(9) << lat_2_deg << "," 
			  << std::setprecision(9) << lon_2_deg << ")" << std::endl;
	
	// Convert coordinates to radians (rad = deg * (pi / 2))
	double lat_1_rad, lon_1_rad, lat_2_rad, lon_2_rad;
	lat_1_rad = lat_1_deg * (boost::math::constants::pi<double>() / 180);
	lon_1_rad = lon_1_deg * (boost::math::constants::pi<double>() / 180);
	lat_2_rad = lat_2_deg * (boost::math::constants::pi<double>() / 180);
	lon_2_rad = lon_2_deg * (boost::math::constants::pi<double>() / 180);

	// Determine latitude and longitude deltas
	double delta_lat, delta_lon;
	delta_lat = lat_1_rad - lat_2_rad;
	delta_lon = lon_1_rad - lon_2_rad;

	// Calculate sin^2 (delta / 2) for both lat and long
	double sdlat = pow(sin(delta_lat / 2), 2);
	double sdlon = pow(sin(delta_lon / 2), 2);

	// Radius of the Earth (approximate)
	const double radius_earth_miles = 3963;
	const double radius_earth_km = 6378;

	// http://en.wikipedia/org/wiki/Haversine_formula
	// d=2r*asin(sqrt(sin^2((lat1-lat2)/2)+cos(l1)cos(l2)sin^2((lon2-lon1)/2)))
	//  if t = sqrt(sin^2((lat1-lat2)/2)+cos(l1)cos(l2)sin^2((lon2-lon1)/2)
	//  -> d = 2 * radius_earth * asin (t)	
	double t = sqrt(sdlat + (cos(lat_1_rad) * cos(lat_2_rad) * sdlon));
	double distance_miles = 2 * radius_earth_miles * asin(t);
	double distance_km = 2 * radius_earth_km * asin(t);

	// Output results
	std::cout << "Distance: " << std::endl;
	std::cout << "  " << std::setprecision(4) << distance_miles 
					  << " miles" << std::endl;
	std::cout << "  " << std::setprecision(4) << distance_km 
					  << " kilometers" << std::endl;
	
	return 0;
}

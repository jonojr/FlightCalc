#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <msclr\marshal_cppstd.h>
#include <fstream>
using namespace std;
class City;
vector<string> cityNames;
vector<City> cities;
struct gps{
	double lat;
	double lon;
};
class airport;
class airport{
	string name, city;
	double lat, lon;
public:
	airport(string name,double lat, double lon) {//Constuctor
		this->name=name;
		setPos(lat, lon);
	}
	airport(){
	}
	string getName() {
		return name;
	}
	void setCity(string city) {
		this->city = city;
	}
	void setPos(double lat, double lon){
		this->lat = lat;
		this->lon = lon;
	}
	gps getPos(){
		gps pos;
		pos.lat = lat;
		pos.lon = lon;
		return pos;
	}
	double getLat(){
		return lat;
	}
	double getLon(){
		return lon;
	}
};
class City{
	string name;
public:
	vector<airport> airports;
	City(string name){//Constructor
		this->name = name;
	}
	City() {}
	void setname(string name){
		this->name = name;
	}
	string getname(){
		return name;	
	}
	//melbourne.addAirport(new airport("Essendon", 30.1, 25.7));
	void addAirport(airport	 port) {
		airports.push_back(port);
		port.setCity(this->getname());
	}
	airport getPortByName(string name) {
		for (int i = 0, ii = airports.size(); i < ii; i++) {
			if (airports[i].getName() == name) {
				return airports[i];
			}
		}
		return airport("NULL", 0, 0);
	}
	int getNumAirports(){
		return airports.size();
	}
};
class flight
	{
	public:
		flight(airport out ,airport in){
			this-> out = out;
			this-> in = in;
			};
	double	calculateDistance(){
        double PI = 4.0*atan(1.0);
        
        //main code inside the class
        double dlat1=out.getLat()*(PI/180);
        double dlong1=out.getLon()*(PI/180);

        double dlat2=in.getLat()*(PI/180);
        double dlong2=in.getLon()*(PI/180);

        double dLong=dlong1-dlong2;
        double dLat=dlat1-dlat2;

        double aHarv= pow(sin(dLat/2.0),2.0)+cos(dlat1)*cos(dlat2)*pow(sin(dLong/2),2);
        double cHarv=2*atan2(sqrt(aHarv),sqrt(1.0-aHarv));
        //earth's radius from wikipedia varies between 6,356.750 km — 6,378.135 km
        //The IUGG value for the equatorial radius of the Earth is 6378.137 km
        const double earth=6378.137;//in km
        double distance=earth*cHarv;
		return distance;// in Km
			}
	string calculateTime(){
		string output;
		float calcTime;
		int hours,mins;
		calcTime = this->calculateDistance()/750;//distance divided by speed
		hours = static_cast <int>(calcTime);
		mins = (calcTime-hours)*60;
		output = to_string(hours);
		output.append(":");
		output.append(to_string(mins));
		return output;
	}
	private:
		airport in;
		airport out;
	};
vector<string> returnCityNames(){
	return cityNames;
}
float findLoc(vector<City>Cities, string name){
	unsigned int iter =0;
	while(iter <= Cities.size()){
		if (Cities[iter].getname() == name){
			return iter;
		}
		iter++;
	}
	return 0.5;
}
void init(){
	cout<<"Initialising please wait"<<endl;
	unsigned int i=0,loc;
	string line,strname,airName,airLat,airLon;
	double dairLat, dairLon;
	vector<string> input;
	ifstream fileinput("Init.dat");
	 while ( getline (fileinput,line) )
    {
      input.push_back(line);
    }
	 City city;
	 while (i<input.size()) // add cities 
	 {
		 if (input[i] != strname){
		 strname = input[i];
		 city = City(strname);
		 cities.push_back(city);
		 }
		 else
		 {
			 cout<<"City is already in database, skipping"<<endl;
		 }
		 i = i+4;
	 }
	 i=0;
	 while(i<input.size()){//add airports to cities
		 loc = findLoc(cities,input[i]);// finds the vector index of the required city
		 if(loc != 0.5){//checks if the city exists
		 airName = input [i+1];
		 airLat = input [i+2];
		 airLon = input [i+3];
		 dairLat = stod(airLat);
		 dairLon = stod(airLon);
		 cities[loc].addAirport(airport(airName,dairLat,dairLon));
		 }
		 else{
			 cout<<"City not found, cannot add airport"<<endl;
		 }
		 i = i+4;
	 }
	}
void createFlight(){
	start:
	int i=0,intOut,intIn,intoutAir,intinAir;
	char out,in,outAir,inAir;
	system("cls");
	while(i < cities.size()){
		cout<<i<<". "<<cities[i].getname()<<endl;
		i++;
	}
	cout<<"Please select you departing city: ";
	cin>>out;
	intOut = out- '0';
	if(isdigit(out) && intOut < cities.size()){
	}
	else
	{
		system("cls");
		cout<<"Error incorrect input"<<endl;
		goto start;
	}
	outport:
	system("cls");
	i=0;
	while(i < cities[intOut].airports.size()){
		cout<<i<<". "<<cities[intOut].airports[i].getName()<<endl;
		i++;
	}
	cout<<"Please select you departing airport: ";
	cin>>outAir;
	intoutAir = outAir - '0';
	if(isdigit(outAir) && intoutAir < cities[intOut].airports.size()){
	}
	else
	{
		system("cls");
		cout<<"Error incorrect input"<<endl;
		goto outport;
	}
	// inbound city
Inbound:
	system("cls");
	i=0;
	while(i < cities.size()){
		cout<<i<<". "<<cities[i].getname()<<endl;
		i++;
	}
	cout<<"Please select you departing city: ";
	cin>>in;
	intIn = in- '0';
	if(isdigit(in) && intIn < cities.size()){
	}
	else
	{
		system("cls");
		cout<<"Error incorrect input"<<endl;
		goto Inbound;
	}
	inport:
	system("cls");
	i=0;
	while(i < cities[intIn].airports.size()){
		cout<<i<<". "<<cities[intIn].airports[i].getName()<<endl;
		i++;
	}
	cout<<"Please select your inbound airport: ";
	cin>>inAir;
	intinAir = inAir - '0';
	if(isdigit(inAir) && intinAir < cities[intIn].airports.size()){
	}
	else
	{
		system("cls");
		cout<<"Error incorrect input"<<endl;
		goto inport;
	}

	flight Flight(cities[intOut].airports[intoutAir],cities[intIn].airports[intinAir]);
	cout<<Flight.calculateDistance()<<" Km"<<endl<<"and will take "<<Flight.calculateTime()<<" hrs:mins"<<endl;
}
void main(){
	init();
	createFlight();
	//flight Flight(cities[findLoc(cities,"Melbourne")].getPortByName("Essendon"),cities[findLoc(cities,"Sydney")].getPortByName("Sydney"));
	//cout<<Flight.calculateDistance()<<" Km"<<endl<<"and will take "<<Flight.calculateTime()<<" hrs:mins"<<endl;
	system("pause");
}
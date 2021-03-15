#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4ParticleDefinition.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "TTree.h"
#include "G4ThreeVector.hh"
#include <fstream>

#define NPBY 50
#define NPBZ 50
using namespace std;
class G4ParticleGun;
class G4GeneralParticleSource;
class G4SPSEneDistribution;
class G4SPSPosDistribution;
class G4SPSAngDistribution;
class G4Event;
class DetectorConstruction;
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

  PrimaryGeneratorAction(G4double,G4int, G4int);
  ~PrimaryGeneratorAction();
  G4double ENER, ESPR, ANGU_X, ANGU_Y, CORR_X, CORR_Y, SPOT_CX, SPOT_CY, SPOT_CZ, SPOT_X, SPOT_Y, SPOT_Z, RAD;

  //MCNPX Function
  void  getRepeatPos(); // reads mcnpx file header.  
  void  getNextPDSet();
  char* ReadFrec();
  void setIOStream(char*);
    
  // Generic function
  vector<G4double> linspace(double , double , int);
  void GeneratePrimaries(G4Event* );
  static G4String GetPrimaryName() ;                
  static inline PrimaryGeneratorAction* GetInstance() { return theGenerator; }

  Float_t x0,y0,z0,px0,py0,pz0;
  Float_t x1,y1,z1,px1,py1,pz1;
  Float_t E0,Estop;
  Int_t   Id;
  Float_t x,y,z,theta,phi,Einit;
  G4ThreeVector Position;
  G4ThreeVector Momentum;
  G4int nProtonsGenerated;   
  G4double IrradiatedEnergy; 
  G4ParticleDefinition* particle;
  G4int A;
  G4int Nprotons;
  vector<G4double> beamPosZ;
  vector<G4double> beamPosY;

  //Pencil beam parameters
  Int_t PencilBeamIdY, PencilBeamIdZ;
  Int_t idPBGlobal, idPBY, idPBZ, ProtonsPerPB;
  vector<G4double> PencilBeamPosY;
  vector<G4double> PencilBeamPosZ;
  Double_t PencilBeamStdY, PencilBeamStdZ, PencilBeamStdAng;

  G4SPSEneDistribution* eneDist;
  G4SPSPosDistribution* posDist;
  G4SPSAngDistribution* angDist;  
  
private:
  static PrimaryGeneratorAction* theGenerator;
  G4GeneralParticleSource*     particleSource;  
  G4ParticleGun*  	       particleGun;  //pointer a to G4 service class

  DetectorConstruction* theDetector;  
  G4double Z_Position;
  G4String PSD_Path;
  G4String PSD_Name;
  G4String PARTICLE;
  G4double fieldSizeZ,fieldSizeY;


  //MCNPX
  std::vector< std::vector<G4double> > pdset;
  int pdtrack;
  int repeatpos;
  int currentpos;
  int recordlength;
  ifstream datafile; // binary phasespace file
  int nrecords;
  int crecord;
  int typetype;
  int ppr;
  int pread;
  G4double x_corr;
  G4double y_corr;
  G4double z_corr;
  G4double x_rot;
  G4double y_rot;
  G4double z_rot;
  G4int p_type;
  char *fname;
  std::map<int,int> particle_lookup;
  
  
};

#endif




* [**What is Pavement-Simulator?**](https://github.com/K1-ZR/pavement-simulator/blob/master/README.md#what-is-pavement-simulator)  

# What is Pavement-Simulator?
Fatigue cracking of the surface layer of a pavements structure is a common distress that reduces the service life of pavement drastically. Accurate prediction of crack propagation in pavement requires to consider the role of underneath layers. *Pavement-Simulator* simulates crack propagation of overlay layer while it takes into account the key features of a pavement structure:  
* Time-dependent behavior of layers  
* Bonding condition between layers  
* Presence of distressed layer or existing joint  

*Pavement-Simulator* is a user-friendly software that generates a simplified 2D FE model of the real problem without losing the key features of the structure.  

<p align="center">
  <img src="https://github.com/K1-ZR/pavement-simulator/blob/master/gallery/pavement-structure.png" width="800" title="all tests">
</p>   

# How Pavement-Simulator works?
Pavement-Simulator divides the structure into squre sections and mesh each section seperately.  The sections are linked to the neighbouring sections by *cohesive elements* (&#8596; shape in the below image). The *cohesive elements* are truss type elements that define the bonding between two adjacent sections and can be one of these three types:

* **No-bonding**: Infinitely weak *cohesive element* such that a sections can move independently with respect to its neighbour section. This type can be used to simulate any preexisting joint or crack.  
* **Perfect-bonding**: Infinitely strong *cohesive element* such that the relative movement of neighbouring sections is zero.  
* **User-defined**: The *cohesive element* properties are defined by the user. This type is used when the bonding is neither a *No-bonding* nor a *Perfect-bonding*. This type is also used where the fatigue cracking or debonding need to be estimated.


<p align="center">
  <img src="https://github.com/K1-ZR/pavement-simulator/blob/master/gallery/pavement-structure-mesh.png" width="800" title="all tests">
</p> 

# How to use Pavement-Simulator?


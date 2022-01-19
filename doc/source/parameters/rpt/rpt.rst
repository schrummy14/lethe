RPT
---
Radioactive particle tracking (RPT) is a non-intrusive velocimetry method which is used to study the hydrodynamics of single and multiphase systems. Launching a RPT simulation for photon count calculation in Lethe requires a solver which is rpt_3d, a parameter file, two files including detector and particle positions inside the vessel. The particle positions file includes either the experimental calibration positions or a set of generated points inside the vessel by the user. Detector positions file contains the position of detector face center and the position of a point inside the detector on its axis. In Lethe-RPT code the middle bottom of the cylinder is considered as the origin. An example of these two files can be find here. This section aims at describing the various parameters available within Lethe-RPT.

In the parameter file format, the parameters are established one by one using the following syntax for instance: 'set reactor radius = 0.1' would fix the reactor radius to 0.1 m. The arguments can be either doubles, integers, or a choice between a predefined condition. In the parameter files, comments are preceded by the sharp symbol (e.g., '#comment').

The parameter file is composed of different subsections. In the following, the principal subsections of a RPT parameter template file are explained.

.. toctree::
   :maxdepth: 1

   RPT_parameters
   Parameter_tuning
   Detector_parameters
   Reconstruction_parameters
   

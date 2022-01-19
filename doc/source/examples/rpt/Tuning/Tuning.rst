============================
Tuning Parameters with NOMAD
============================

In this example in order to test the ability of NOMAD to predict the unknowns variables of the beam model (Detector dead time, Source activity, Reactor attenuation coefficient ) from noisy data, we have generated an artificial set of experimental counts which are exposed to the noise. To generate this data set we have applied noise on particle positions with a normal distribution (mu = 0, sigma = 2 mm), then we have calculated the counts on the new set of particle positions. Using the real particle positions with noisy counts provides us the opportunity of testing NOMAD on noisy experimental data set.



Parameter file
--------------

In the subsection “rpt parameters”, we define a set of real positions (theoretical values of inside the reactor. Common parameters for the RPT simulation are described in the RPT parameters subsection in the RPT Parameters documentation.

.. warning:: 
     verbosity MUST be "quiet" since NOMAD get the cost function value in terminal for its MADS algorithm.

.. code-block:: text

    # --------------------------------------------------
    # RPT Monte Carlo technique
    #---------------------------------------------------
    subsection rpt parameters
        set particle positions file          = real_positions.particle
        set verbosity                        = quiet
        set export counts                    = false
        set counts file                      = run.csv
        set monte carlo iteration            = 10000
        set random number seed               = 0
        set reactor radius       			 = 0.1
        set peak-to-total ratio  			 = 0.4
        set sampling time        			 = 1
        set gamma-rays emitted        		 = 2
        set attenuation coefficient detector = 21.477
    
    end

In the subsection “parameter tuning”, we enable parameters tuning, specify a type of cost function and define a set of artificial counts to compare with calculated counts. Parameters used of the tuning of the model parameters are described in the RPT Parameters documentation.

.. code-block:: text

    # --------------------------------------------------
    # Initial value of parameters for tuning
    #---------------------------------------------------
    subsection parameter tuning
        set tuning                           = true
        set cost function type               = larachi
        set experimental data file           = noisy_counts.experimental
    end

In the subsection “detector parameters”, we specify the file that contains the position of the detector face center and the position of a point inside the detector on its axis. The detector parameters are described in the RPT Parameters documentation.

.. code-block:: text

    #---------------------------------------------------
    # Detector parameters
    #---------------------------------------------------
    subsection detector parameters
	    set detector positions file          = positions.detector
        set radius       			    	 = 0.0381 
        set length					         = 0.0762
        set dead time       				 = 1e-5
        set activity  						 = 2e6
        set attenuation coefficient reactor  = 10
    end

READ ME file
------------

To use NOMAD with the rpt_3d application you need to :

* Modify the paths in script "rpt_nomad_lethe.py"
* Modify the initial guess of parameters and number of black box evaluations for NOMAD in "param_nomad.txt"
* Run NOMAD with its parameter file with => /path/to/NOMAD/ param_nomad.txt

How it works:

* NOMAD will execute the Python script which in provided by the "param_nomad.txt" file.
* The Python script "rpt_nomad_lethe.py" proceeds the values of parameters to tune gave by NOMAD, modifies the parameter file for Lethe and runs the rpt_3d application.
* rpt_3d of Lethe executes the Monte Carlo ray model and calculates a cost function which is got by NOMAD
* NOMAD executes its MADS algorithm and generates new set of parameters until a criteria

Result
~~~~~~

The best feasible solution reported by NOMAD gives the following values for each unknown.

.. code-block:: text

    # --------------------------------------------------
    # Best feasible solution
    #---------------------------------------------------
    Detector dead time                   = 1.064e-5
    Source activity                      = 2.03125e6
    Reactor attenuation coefficient      = 10.1539


The real values to generate the artificial data set as mentioned in parameter file section are:

.. code-block:: text
    
    # --------------------------------------------------
    # Real values for generating data set
    #---------------------------------------------------
    Detector dead time                   = 1e-5
    Source activity                      = 2e6
    Reactor attenuation coefficient      = 10






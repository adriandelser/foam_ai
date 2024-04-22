/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2021 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    pisoFoam

Description
    Transient solver for incompressible, turbulent flow, using the PISO
    algorithm.

    Sub-models include:
    - turbulence modelling, i.e. laminar, RAS or LES
    - run-time selectable MRF and finite volume options, e.g. explicit porosity

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "singlePhaseTransportModel.H"
#include "kinematicMomentumTransportModel.H"
#include "pisoControl.H"
#include "pressureReference.H"
#include "fvModels.H"
#include "fvConstraints.H"
#include <ctime>
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <arrayobject.h>
//#include "/home/daep/a.del-ser/.local/lib/python3.8/site-packages/numpy/core/include/numpy/arrayobject.h"
/*
#include "/home/daep/a.del-ser/.local/lib/python3.8/site-packages/numpy/core/include/numpy/ndarrayobject.h"
#include "/home/daep/a.del-ser/.local/lib/python3.8/site-packages/numpy/core/include/numpy/npy_interrupt.h"
#include "/home/daep/a.del-ser/.local/lib/python3.8/site-packages/numpy/core/include/numpy/noprefix.h"
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])

{
    
    #include "postProcess.H"
    #include "pyComm1.H"

    #include "setRootCaseLists.H"
    
    #include "createTime.H"
    #include "createMesh.H"

    #include "createControl.H"
    #include "createFields.H"

    #include "initContinuityErrs.H"
    //#include "pyComm2.H"
    //const volVectorField& C = mesh.C();         // Cell center coordinates
  //  Info << mesh << nl << endl;
    

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;
 //   Info<< U << nl << endl;
    //these are the variables that store time taken for specific parts of the algorithm
    float pTime = 0;
    float pTimeBuffer = 0;
    float uTime = 0;
    float uTimeBuffer = 0;
    
    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        #include "CourantNo.H"

        // Pressure-velocity PISO corrector
        {
            fvModels.correct();
	    uTimeBuffer = runTime.elapsedCpuTime();
            #include "UEqn.H"
            uTime += runTime.elapsedCpuTime() - uTimeBuffer;
            // --- PISO loop
            
            /*The code below just writes time whenever we want
            Info<< "sup, it's before pressure lmao = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
            */
            
            //store the current elapsed Cpu time in a buffer
            pTimeBuffer = runTime.elapsedCpuTime();
            
            //run the pressure correction loop
            while (piso.correct())
            {
                #include "pEqn.H"
            }
            //add the time taken for this loop to the total pTime
            pTime += runTime.elapsedCpuTime() - pTimeBuffer;
            
            /*// this is some more printing chaos
            Info<< "sup, it's after pressure lmao = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
            */
            //#include "pyComm2.H"
        }

        laminarTransport.correct();
        turbulence->correct();

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << "  pTime = " << pTime << " s"
            << "  uTime = " << uTime << " s"
            << nl << endl;
    }
    Info<< "End\n" << endl;
     
    //Info<< U << nl << endl;
    //#include "numpyTest.H"
    //#include "pyComm1Test.H"
   //#include "pyComm1.H"
    #include "pyComm2.H"

    return 0;
}


// ************************************************************************* //

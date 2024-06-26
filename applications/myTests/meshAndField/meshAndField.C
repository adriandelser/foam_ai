/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2021 OpenFOAM Foundation
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
    meshAndField

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
 
	/*Info<< "Create mesh" << endl;

	fvMesh mesh

	(
	IOobject

	(
	fvMesh::defaultRegion,

	runTime.timeName(),

	runTime,

	IOobject::MUST_READ
	)
	);
	*/

	Info<< "Cell centres" << nl << mesh.cellCentres() << endl;

	Info<< "Cell volumes" << nl << mesh.cellVolumes() << endl;

	Info<< "Cell face centres" << nl << mesh.faceCentres() << endl; 

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    	Info<< mesh.C() << endl;

	Info<< mesh.V() << endl;

	Info<< mesh.Cf() << endl;
   
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< nl << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;

    Info<< "End\n" << endl;
    
    
   /*	Info<< nl;

	runTime.printExecutionTime(Info);

	Info<< "End\n" << endl;
	*/

    return 0;
}


// ************************************************************************* //

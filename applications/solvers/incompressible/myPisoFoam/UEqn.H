// Solve the Momentum equation
Info<< "Start of UEqn.H" << nl << endl;
MRF.correctBoundaryVelocity(U);

fvVectorMatrix UEqn
(
    fvm::ddt(U) + fvm::div(phi, U)
  + MRF.DDt(U)
  + turbulence->divDevSigma(U)
 ==
    fvModels.source(U)
);

UEqn.relax();

fvConstraints.constrain(UEqn);

if (piso.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvConstraints.constrain(U);
}


//Info<< U << nl << endl;
Info<< "End of UEqn.H" << nl << endl;

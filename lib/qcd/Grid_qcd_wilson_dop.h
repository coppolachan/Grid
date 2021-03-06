#ifndef  GRID_QCD_WILSON_DOP_H
#define  GRID_QCD_WILSON_DOP_H


namespace Grid {

  namespace QCD {

  // Should be in header?
    const int Xp = 0;
    const int Yp = 1;
    const int Zp = 2;
    const int Tp = 3;
    const int Xm = 4;
    const int Ym = 5;
    const int Zm = 6;
    const int Tm = 7;

    class WilsonMatrix : public CheckerBoardedSparseMatrixBase<LatticeFermion>
    {
      //NB r=1;
    public:
      static int HandOptDslash;

      double                        mass;
      //      GridBase                     *    grid; // Inherited
      //      GridBase                     *  cbgrid;

      //Defines the stencils for even and odd
      CartesianStencil Stencil; 
      CartesianStencil StencilEven; 
      CartesianStencil StencilOdd; 

      // Copy of the gauge field , with even and odd subsets
      LatticeDoubledGaugeField Umu;
      LatticeDoubledGaugeField UmuEven;
      LatticeDoubledGaugeField UmuOdd;

      static const int npoint=8;
      static const std::vector<int> directions   ;
      static const std::vector<int> displacements;
      static const int Xp,Xm,Yp,Ym,Zp,Zm,Tp,Tm;

      // Comms buffer
      std::vector<vHalfSpinColourVector,alignedAllocator<vHalfSpinColourVector> >  comm_buf;

      // Constructor
      WilsonMatrix(LatticeGaugeField &_Umu,GridCartesian &Fgrid,GridRedBlackCartesian &Hgrid,double _mass);

      // DoubleStore
      void DoubleStore(LatticeDoubledGaugeField &Uds,const LatticeGaugeField &Umu);

      // override multiply
      virtual RealD  M    (const LatticeFermion &in, LatticeFermion &out);
      virtual RealD  Mdag (const LatticeFermion &in, LatticeFermion &out);

      // half checkerboard operaions
      virtual void   Meooe       (const LatticeFermion &in, LatticeFermion &out);
      virtual void   MeooeDag    (const LatticeFermion &in, LatticeFermion &out);
      virtual void   Mooee       (const LatticeFermion &in, LatticeFermion &out);
      virtual void   MooeeDag    (const LatticeFermion &in, LatticeFermion &out);
      virtual void   MooeeInv    (const LatticeFermion &in, LatticeFermion &out);
      virtual void   MooeeInvDag (const LatticeFermion &in, LatticeFermion &out);

      // non-hermitian hopping term; half cb or both
      void Dhop  (const LatticeFermion &in, LatticeFermion &out,int dag);
      void DhopOE(const LatticeFermion &in, LatticeFermion &out,int dag);
      void DhopEO(const LatticeFermion &in, LatticeFermion &out,int dag);
      void DhopInternal(CartesianStencil & st,LatticeDoubledGaugeField &U,
			const LatticeFermion &in, LatticeFermion &out,int dag);

      typedef iScalar<iMatrix<vComplex, Nc> > matrix;

      
    };


    class DiracOpt {
    public:
      // These ones will need to be package intelligently. WilsonType base class
      // for use by DWF etc..
      static void DhopSite(CartesianStencil &st,LatticeDoubledGaugeField &U,
		    std::vector<vHalfSpinColourVector,alignedAllocator<vHalfSpinColourVector> >  &buf,
		    int ss,const LatticeFermion &in, LatticeFermion &out);
      static void DhopSiteDag(CartesianStencil &st,LatticeDoubledGaugeField &U,
		       std::vector<vHalfSpinColourVector,alignedAllocator<vHalfSpinColourVector> >  &buf,
		       int ss,const LatticeFermion &in, LatticeFermion &out);

    };
    class DiracOptHand {
    public:
      // These ones will need to be package intelligently. WilsonType base class
      // for use by DWF etc..
      static void DhopSite(CartesianStencil &st,LatticeDoubledGaugeField &U,
		    std::vector<vHalfSpinColourVector,alignedAllocator<vHalfSpinColourVector> >  &buf,
		    int ss,const LatticeFermion &in, LatticeFermion &out);
      static void DhopSiteDag(CartesianStencil &st,LatticeDoubledGaugeField &U,
		       std::vector<vHalfSpinColourVector,alignedAllocator<vHalfSpinColourVector> >  &buf,
		       int ss,const LatticeFermion &in, LatticeFermion &out);

    };

  }
}
#endif

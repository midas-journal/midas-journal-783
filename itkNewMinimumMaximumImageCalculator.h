/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkNewMinimumMaximumImageCalculator.h,v $
  Language:  C++
  Date:      $Date: 2009-04-25 12:27:32 $
  Version:   $Revision: 1.17 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNewMinimumMaximumImageCalculator_h
#define __itkNewMinimumMaximumImageCalculator_h

#include "itkObject.h"
#include "itkObjectFactory.h"

namespace itk
{

/** \class NewMinimumMaximumImageCalculator
 * This calculator computes the minimum and the maximum intensity values of
 * an image.  It is templated over input image type.  If only Maximum or
 * Minimum value is needed, just call ComputeMaximum() (ComputeMinimum())
 * otherwise Compute() will compute both. 
 * To exclude a value for the computation use that value as an arguement 
 * to the Compute functions.
 * All indices containing a pixel of maximum/minimum intensity value
 * are saved in m_IndicesOfMaximum and m_IndicesOfMinimum
 *
 * \ingroup Operators
 */
template <class TInputImage>
class ITK_EXPORT NewMinimumMaximumImageCalculator : public Object 
{
public:
  /** Standard class typedefs. */
  typedef NewMinimumMaximumImageCalculator Self;
  typedef Object                        Superclass;
  typedef SmartPointer<Self>            Pointer;
  typedef SmartPointer<const Self>      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(NewMinimumMaximumImageCalculator, Object);

  /** Type definition for the input image. */
  typedef TInputImage  ImageType;

  /** Pointer type for the image. */
  typedef typename TInputImage::Pointer  ImagePointer;
  
  /** Const Pointer type for the image. */
  typedef typename TInputImage::ConstPointer ImageConstPointer;

  /** Type definition for the input image pixel type. */
  typedef typename TInputImage::PixelType PixelType;
  
  /** Type definition for the input image index type. */
  typedef typename TInputImage::IndexType IndexType;
  
  /** Type definition for the input image region type. */
  typedef typename TInputImage::RegionType RegionType;
  
  /** Type definition for vector holding indices of pixels. */
  typedef std::vector<IndexType> VectorType;
  
  /** Set the input image. */
  itkSetConstObjectMacro(Image,ImageType);

  /** Compute the minimum value of intensity of the input image. */
  void ComputeMinimum(void);
  
  /** Compute the minimum value of intensity of the input image while excluding pixels 
      with a value of excludeMin. */
  void ComputeMinimum(PixelType excludeMin);

  /** Compute the maximum value of intensity of the input image. */
  void ComputeMaximum(void);

  /** Compute the maximum value of intensity of the input image while excluding 
      pixels with a value of excludeMax */
  void ComputeMaximum(PixelType excludeMax);

  /** Compute the minimum and maximum values of intensity of the input image. */
  void Compute(void);
  
  /** Compute the minimum and maximum values of intensity of the input image while 
      excluding pixels with values excludeMin and excludeMax. */
  void Compute(PixelType excludeMin, PixelType excludeMax);

  /** Return the minimum intensity value. */
  itkGetConstMacro(Minimum,PixelType);
  
  /** Return the maximum intensity value. */
  itkGetConstMacro(Maximum,PixelType);

  /** Return the index of the minimum intensity value. */
  itkGetConstReferenceMacro(IndexOfMinimum,IndexType);

  /** Return indices of pixels with minimum intensity value. */
  VectorType GetIndicesOfMinimum(void) {return m_IndicesOfMinimum;}

  /** Return the index of the maximum intensity value. */
  itkGetConstReferenceMacro(IndexOfMaximum,IndexType);

  /** Return indices of pixels with maximum intensity value. */
  VectorType GetIndicesOfMaximum(void) {return m_IndicesOfMaximum;}
  
  /** Set the region over which the values will be computed */
  void SetRegion( const RegionType & region );

protected:
  NewMinimumMaximumImageCalculator();
  virtual ~NewMinimumMaximumImageCalculator() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  NewMinimumMaximumImageCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
  PixelType            m_Minimum;
  PixelType            m_Maximum;
  ImageConstPointer    m_Image;

  IndexType            m_IndexOfMinimum;
  IndexType            m_IndexOfMaximum;
  
  VectorType           m_IndicesOfMinimum;
  VectorType           m_IndicesOfMaximum;

  RegionType           m_Region;
  bool                 m_RegionSetByUser;
};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkNewMinimumMaximumImageCalculator.txx"
#endif

#endif /* __itkNewMinimumMaximumImageCalculator_h */

/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkNewMinimumMaximumImageCalculator.txx,v $
  Language:  C++
  Date:      $Date: 2008-10-16 23:24:23 $
  Version:   $Revision: 1.23 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNewMinimumMaximumImageCalculator_txx
#define __itkNewMinimumMaximumImageCalculator_txx

#include "itkNewMinimumMaximumImageCalculator.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkNumericTraits.h"

namespace itk
{ 
    
/**
 * Constructor
 */
template<class TInputImage>
NewMinimumMaximumImageCalculator<TInputImage>
::NewMinimumMaximumImageCalculator()
{
  m_Image = TInputImage::New();
  m_Maximum = NumericTraits<PixelType>::NonpositiveMin();
  m_Minimum = NumericTraits<PixelType>::max();
  m_IndexOfMinimum.Fill(0);
  m_IndexOfMaximum.Fill(0);
  m_IndicesOfMinimum.push_back(m_IndexOfMinimum);
  m_IndicesOfMaximum.push_back(m_IndexOfMaximum);
  m_RegionSetByUser = false;
}


/**
 * Compute Min and Max of m_Image
 */
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::Compute(void)
{
  if( !m_RegionSetByUser )
    {
    m_Region = m_Image->GetRequestedRegion();
    }

  ImageRegionConstIteratorWithIndex< TInputImage >  it( m_Image, m_Region );
  m_Maximum = NumericTraits<PixelType>::NonpositiveMin();
  m_Minimum = NumericTraits<PixelType>::max();


  while( !it.IsAtEnd() )
    {
    const PixelType value = it.Get();  
    if (value > m_Maximum) 
      {
      m_Maximum = value;
      m_IndexOfMaximum = it.GetIndex();
      }
    if (value < m_Minimum) 
      {
      m_Minimum = value;
      m_IndexOfMinimum = it.GetIndex();
      }
    ++it;
    }

  m_IndicesOfMaximum.clear();
  m_IndicesOfMinimum.clear();
  it.GoToBegin();
  while( !it.IsAtEnd() )
    {
    if (it.Get() == m_Maximum)
      m_IndicesOfMaximum.push_back(it.GetIndex());
    if (it.Get() == m_Minimum)
      m_IndicesOfMinimum.push_back(it.GetIndex());
    ++it; 
    }
}

/**
 * Compute Min and Max of m_Image
 * while excluding pixels with values excludeMin and excludeMax
 */
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::Compute(PixelType excludeMin, PixelType excludeMax)
{
  if( !m_RegionSetByUser )
    {
    m_Region = m_Image->GetRequestedRegion();
    }

  ImageRegionConstIteratorWithIndex< TInputImage >  it( m_Image, m_Region );
  m_Maximum = NumericTraits<PixelType>::NonpositiveMin();
  m_Minimum = NumericTraits<PixelType>::max();


  while( !it.IsAtEnd() )
    {
    const PixelType value = it.Get();  
    if (value > m_Maximum && value != excludeMax) 
      {
      m_Maximum = value;
      m_IndexOfMaximum = it.GetIndex();
      }
    if (value < m_Minimum && value != excludeMin) 
      {
      m_Minimum = value;
      m_IndexOfMinimum = it.GetIndex();
      }
    ++it;
    }

  m_IndicesOfMaximum.clear();
  m_IndicesOfMinimum.clear();
  it.GoToBegin();
  while( !it.IsAtEnd() )
    {
    if (it.Get() == m_Maximum)
      m_IndicesOfMaximum.push_back(it.GetIndex());
    if (it.Get() == m_Minimum)
      m_IndicesOfMinimum.push_back(it.GetIndex());
    ++it; 
    }
}

/**
 * Compute the minimum intensity value of the image
 */
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::ComputeMinimum(void)
{
  if( !m_RegionSetByUser )
    {
    m_Region = m_Image->GetRequestedRegion();
    }
  ImageRegionConstIteratorWithIndex< TInputImage >  it( m_Image,  m_Region );
  m_Minimum = NumericTraits<PixelType>::max();

  while( !it.IsAtEnd() )
    {
    const PixelType value = it.Get();  
    if (value < m_Minimum) 
      {
      m_Minimum = value;
      m_IndexOfMinimum = it.GetIndex();
      }
    ++it;
    }

  m_IndicesOfMinimum.clear();
  m_IndicesOfMinimum.push_back(m_IndexOfMinimum);
  it.GoToBegin();
  while( !it.IsAtEnd() )
    {
    if (it.Get() == m_Minimum)
      m_IndicesOfMinimum.push_back(it.GetIndex());
    ++it; 
    }
}

/**
 * Compute the minimum intensity value of the image while
 * excluding pixels with value excludeMin.
 */
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::ComputeMinimum(PixelType excludeMin)
{
  if( !m_RegionSetByUser )
    {
    m_Region = m_Image->GetRequestedRegion();
    }
  ImageRegionConstIteratorWithIndex< TInputImage >  it( m_Image,  m_Region );
  m_Minimum = NumericTraits<PixelType>::max();

  while( !it.IsAtEnd() )
    {
    const PixelType value = it.Get();  
    if (value < m_Minimum && value != excludeMin) 
      {
      m_Minimum = value;
      m_IndexOfMinimum = it.GetIndex();
      }
    ++it;
    }

  m_IndicesOfMinimum.clear();
  it.GoToBegin();
  while( !it.IsAtEnd() )
    {
    if (it.Get() == m_Minimum)
      m_IndicesOfMinimum.push_back(it.GetIndex());
    ++it; 
    }
}

/**
 * Compute the maximum intensity value of the image
 */
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::ComputeMaximum(void)
{
  if( !m_RegionSetByUser )
    {
    m_Region = m_Image->GetRequestedRegion();
    }
  ImageRegionConstIteratorWithIndex< TInputImage >  it( m_Image,  m_Region );
  m_Maximum = NumericTraits<PixelType>::NonpositiveMin();

  while( !it.IsAtEnd() )
    {
    const PixelType value = it.Get();  
    if (value > m_Maximum) 
      {
      m_Maximum = value;
      m_IndexOfMaximum = it.GetIndex();
      }
    ++it;
    }
    
  m_IndicesOfMaximum.clear();
  it.GoToBegin();
  while( !it.IsAtEnd() )
    {
    if (it.Get() == m_Maximum)
      m_IndicesOfMaximum.push_back(it.GetIndex());
    ++it; 
    }
}

/**
 * Compute the maximum intensity value of the image while
 * excluding pixels with value excludeMax.
 */
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::ComputeMaximum(PixelType excludeMax)
{
  if( !m_RegionSetByUser )
    {
    m_Region = m_Image->GetRequestedRegion();
    }
  ImageRegionConstIteratorWithIndex< TInputImage >  it( m_Image,  m_Region );
  m_Maximum = NumericTraits<PixelType>::NonpositiveMin();

  while( !it.IsAtEnd() )
    {
    const PixelType value = it.Get();  
    if (value > m_Maximum && value != excludeMax) 
      {
      m_Maximum = value;
      m_IndexOfMaximum = it.GetIndex();
      }
    ++it;
    }

  m_IndicesOfMaximum.clear();
  it.GoToBegin();
  while( !it.IsAtEnd() )
    {
    if (it.Get() == m_Maximum)
      m_IndicesOfMaximum.push_back(it.GetIndex());
    ++it; 
    }
}

template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::SetRegion( const RegionType & region )
{
  m_Region = region;
  m_RegionSetByUser = true;
}


 
template<class TInputImage>
void
NewMinimumMaximumImageCalculator<TInputImage>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "Minimum: "
     << static_cast<typename NumericTraits<PixelType>::PrintType>(m_Minimum)
     << std::endl;
  os << indent << "Maximum: "
     << static_cast<typename NumericTraits<PixelType>::PrintType>(m_Maximum)
     << std::endl;
  os << indent << "Index of Minimum: " << m_IndexOfMinimum << std::endl;
  os << indent << "Index of Maximum: " << m_IndexOfMaximum << std::endl;
  os << indent << "Image: " << std::endl;
  m_Image->Print(os, indent.GetNextIndent());
  os << indent << "Region: " << std::endl;
  m_Region.Print(os,indent.GetNextIndent());
  os << indent << "Region set by User: " << m_RegionSetByUser << std::endl;
  os << indent << "Indices of Minimum: " << std::endl;
  for(unsigned int i = 0; i < m_IndicesOfMinimum.size(); i++)
    os << indent << m_IndicesOfMinimum[i] << std::endl;
  os << indent << "Indices of Maximum: " << std::endl;
  for(unsigned int i = 0; i < m_IndicesOfMaximum.size(); i++)
    os << indent << m_IndicesOfMaximum[i] << std::endl;
  
}

} // end namespace itk

#endif

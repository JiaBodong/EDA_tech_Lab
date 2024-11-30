#pragma once

#include "utils.hpp"
#include "truth_table.hpp"
#include "operators.hpp"

#include <cassert>

inline Truth_Table Truth_Table::positive_cofactor( uint8_t const var ) const
{
  assert( var < this->num_vars() );
  /* TODO */
  Truth_Table result( this->num_vars() );
  uint64_t  mask = this->_bits & var_mask_pos[var]; //get the mask for the variable

  mask = (mask >> (1 << var)) | mask ; //shift the mask to the right and or it with the original mask
  result.set_bits(mask);

  return result;
}

inline Truth_Table Truth_Table::negative_cofactor( uint8_t const var ) const
{
  assert( var < this->num_vars() );
  Truth_Table result( this->num_vars() );
  /* TODO */

  uint64_t  mask = this->_bits & var_mask_neg[var]; //get the mask for the variable

  mask = (mask << (1 << var)) | mask ; 
  result.set_bits(mask);

  return result;
}

inline Truth_Table Truth_Table::derivative( uint8_t const var ) const
{
  assert( var < this->num_vars() );
  
  /* TODO */
  Truth_Table pos = positive_cofactor(var);
  Truth_Table neg = negative_cofactor(var);
  Truth_Table result = pos ^ neg;


  return result;
}

inline Truth_Table Truth_Table::consensus( uint8_t const var ) const
{
  assert( var < this->num_vars() );
  
  /* TODO */
  Truth_Table pos = positive_cofactor(var);
  Truth_Table neg = negative_cofactor(var);
  Truth_Table result = pos & neg;
  return result;
}

inline Truth_Table Truth_Table::smoothing( uint8_t const var ) const
{
  assert( var < this->num_vars() );

  /* TODO */

  Truth_Table pos = positive_cofactor(var);
  Truth_Table neg = negative_cofactor(var);
  Truth_Table result = pos | neg;
  return result;
}
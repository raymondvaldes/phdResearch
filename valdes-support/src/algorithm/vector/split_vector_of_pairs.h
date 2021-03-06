//
//  split_vector_of_pairs.h
//  tat
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_algorithm_vector_split_vector_of_pairs_h
#define tat_algorithm_vector_split_vector_of_pairs_h

#include <vector>
#include <utility>
#include "algorithm/algorithm.h"

namespace algorithm {
namespace vector{
  
template< typename T_1, typename T_2 >
auto split_vector_of_pairs
(
  std::vector< std::pair< T_1, T_2 > > const & pairs
)
noexcept -> std::pair< std::vector< T_1 >, std::vector< T_2 > >
{
  assert( !pairs.empty() );
  
  using std::make_pair;
  using algorithm::transform;
  using std::vector;
  
  
  auto list_first = vector< T_1 >() ;
  auto list_second = vector< T_2 >() ;
  
  for_each( pairs, [&list_first, &list_second]( auto const & pair ) noexcept
  {
    list_first.emplace_back( pair.first );
    list_second.emplace_back( pair.second );
  } );

  
  return make_pair( list_first, list_second );
}
  
} // namespace vector
} // namespace algorithm

#endif

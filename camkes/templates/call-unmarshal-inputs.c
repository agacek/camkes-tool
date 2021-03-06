/*# We expect the following variables to be defined when this fragment is
 *# included.
 #*/
/*? assert(isinstance(function, basestring)) ?*/     /*# Name of function to create #*/
/*? assert(isinstance(size, basestring)) ?*/         /*# Name of a variable storing the byte length of the message #*/
/*? assert(isinstance(input_parameters, list)) ?*/   /*# All input parameters to this method #*/

/*? function ?*/(
/*? size ?*/
/*- if len(input_parameters) > 0 -*/
  ,
/*- endif -*/
/*- for p in input_parameters -*/
  /*- if p.array -*/
    /*? p.name ?*/_sz_ptr,
  /*- endif -*/
  /*? p.name ?*/_ptr
  /*- if not loop.last -*/
    ,
  /*- endif -*/
/*- endfor -*/
)

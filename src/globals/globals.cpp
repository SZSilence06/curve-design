#include "globals.h"

var_pt_store globals;

var_pt_store& get_globals(void)
{
	return globals;
}

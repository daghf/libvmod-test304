#include <stdlib.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

unsigned __match_proto__() 
vmod_test304(struct sess *sp)
{
	return (sp->obj->response == 200 &&
	    sp->http->conds &&
	    RFC2616_Do_Cond(sp));
}

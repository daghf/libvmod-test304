============
vmod_test304
============

----------------------
Varnish test304 Module
----------------------

:Author: Dag Haavi Finstad
:Date: 2013-12-02
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

import test304;

DESCRIPTION
===========

Lets you detect if the current response will end up as a 304 Not
Modified. Must only be used in vcl_deliver.

The 304 logic in Varnish depends on whether or not any of the relevant
headers were altered in vcl_deliver, so in general we can't know until
after vcl_deliver if this response will end up as a 304.

To rely on the result from the test304() function, you must not alter
either of the following after the call::
  
  req.http.if-modified-since
  req.http.if-none-match

Varnish uses the headers of the fetched object (not the copy in
resp.http.*) when deciding if it will do a 304, so stripping off
resp.http.etag or resp.http.last-modified in vcl_deliver will prevent
the client from seeing these, but will not prevent Varnish from
serving a 304.

FUNCTIONS
=========

test304
-------

Prototype
        ::

                test304()
Return value
	BOOL
Description
	Returns true if this response will end up as a 304. Do not 
	invoke this from outside of vcl_deliver.
Example
        ::

	   sub vcl_deliver {
	       if (test304.test304()) {
	           set resp.http.foo = "this is a 304";
	       }
	   }



INSTALLATION
============

This is an example skeleton for developing out-of-tree Varnish
vmods available from the 3.0 release. It implements the "Hello, World!" 
as a vmod callback. Not particularly useful in good hello world 
tradition,but demonstrates how to get the glue around a vmod working.

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines::
        
        import example;

        sub vcl_deliver {
                # This sets resp.http.hello to "Hello, World"
                set resp.http.hello = example.hello("World");
        }

HISTORY
=======

This manual page was released as part of the libvmod-example package,
demonstrating how to create an out-of-tree Varnish vmod. For further
examples and inspiration check the vmod directory:
 https://www.varnish-cache.org/vmods

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-example project. See LICENSE for details.

* Copyright (c) 2011 Varnish Software

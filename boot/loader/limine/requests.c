/**
 * @file boot/loader/limine/requests.c
 * @brief limine requests
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

#include "limine.h"

#define __limine_req

/**
 * Request Limine revision 2
 */
__limine_req
static volatile LIMINE_BASE_REVISION(2);


/** 
 * Every request will be between those tags.
 * This tag...
 */
__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

    

/**
 * ...and this tag.
 */
__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;
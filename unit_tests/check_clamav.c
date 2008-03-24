#if HAVE_CONFIG_H
#include "clamav-config.h"
#endif

#include <stdio.h>

#ifndef HAVE_CHECK
int main(int argc, char **argv)
{
    printf("Unit tests disabled in build\n");
    return 0;
}
#else

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <check.h>
#include "../libclamav/clamav.h"
#include "../libclamav/others.h"
#include "../libclamav/matcher.h"

/* extern void cl_free(struct cl_engine *engine); */
START_TEST (test_cl_free)
/*
    struct cl_engine *engine = NULL;
    cl_free(NULL);
*/
END_TEST

/* extern struct cl_engine *cl_dup(struct cl_engine *engine); */
START_TEST (test_cl_dup)
    /*
    struct cl_engine *engine;
    fail_unless(NULL == cl_dup(NULL), "cl_dup null pointer");
    */
END_TEST

/* extern int cl_build(struct cl_engine *engine); */
START_TEST (test_cl_build)
    /*
    struct cl_engine *engine;
    fail_unless(CL_ENULLARG == cl_build(NULL), "cl_build null pointer");
    engine = calloc(sizeof(struct cl_engine),1);
    fail_unless(engine, "cl_build calloc");
    fail_unless(CL_ENULLARG == cl_build(engine), "cl_build(engine) with null ->root");
    */
/*    engine->root = cli_calloc(CL_TARGET_TABLE_SIZE, sizeof(struct cli_matcher *)); */
END_TEST

/* extern void cl_debug(void); */
START_TEST (test_cl_debug)
    cli_debug_flag = 0;
    cl_debug();
    fail_unless(1 == cli_debug_flag, "cl_debug failed to set cli_debug_flag");

    cli_debug_flag = 1;
    cl_debug();
    fail_unless(1 == cli_debug_flag, "cl_debug failed when flag was already set");
END_TEST

/* extern const char *cl_retdbdir(void); */
START_TEST (test_cl_retdbdir)
    fail_unless(!strcmp(DATADIR, cl_retdbdir()), "cl_retdbdir");
END_TEST

/* extern const char *cl_retver(void); */
START_TEST (test_cl_retver)
    fail_unless(!strcmp(VERSION, cl_retver()), "cl_retver");
END_TEST

/* extern void cl_cvdfree(struct cl_cvd *cvd); */
START_TEST (test_cl_cvdfree)
/*
    struct cl_cvd *cvd1, *cvd2;

    cvd1 = malloc(sizeof(struct cl_cvd));
    fail_unless(cvd1, "cvd malloc");
    cl_cvdfree(cvd1);

    cvd2 = malloc(sizeof(struct cl_cvd));
    cvd2->time = malloc(1);
    cvd2->md5 = malloc(1);
    cvd2->dsig= malloc(1);
    cvd2->builder = malloc(1);
    fail_unless(cvd2, "cvd malloc");
    fail_unless(cvd2->time, "cvd malloc");
    fail_unless(cvd2->md5, "cvd malloc");
    fail_unless(cvd2->dsig, "cvd malloc");
    fail_unless(cvd2->builder, "cvd malloc");
    cl_cvdfree(cvd2);
    cl_cvdfree(NULL);
*/
END_TEST

/* extern int cl_statfree(struct cl_stat *dbstat); */
START_TEST (test_cl_statfree)
/*
    struct cl_stat *stat;
    fail_unless(CL_ENULLARG == cl_statfree(NULL), "cl_statfree(NULL)");
    
    stat = malloc(sizeof(struct cl_stat));
    fail_unless(NULL != stat, "malloc");
    fail_unless(CL_SUCCESS == cl_statfree(stat), "cl_statfree(empty_struct)");
    
    stat = malloc(sizeof(struct cl_stat));
    fail_unless(NULL != stat, "malloc");
    stat->stattab = strdup("test");
    fail_unless(NULL != stat->stattab, "strdup");
    fail_unless(CL_SUCCESS == cl_statfree(stat), "cl_statfree(stat with stattab)");

    stat = malloc(sizeof(struct cl_stat));
    fail_unless(NULL != stat, "malloc");
    stat->stattab = NULL;
    fail_unless(CL_SUCCESS == cl_statfree(stat), "cl_statfree(stat with stattab) set to NULL");
*/
END_TEST

/* extern unsigned int cl_retflevel(void); */
START_TEST (test_cl_retflevel)
END_TEST    

/* extern struct cl_cvd *cl_cvdhead(const char *file); */
START_TEST (test_cl_cvdhead)
/*
    fail_unless(NULL == cl_cvdhead(NULL), "cl_cvdhead(null)");
    fail_unless(NULL == cl_cvdhead("input/cl_cvdhead/1.txt"), "cl_cvdhead(515 byte file, all nulls)");
*/
    /* the data read from the file is passed to cl_cvdparse, test cases for that are separate */
END_TEST

/* extern struct cl_cvd *cl_cvdparse(const char *head); */
START_TEST (test_cl_cvdparse)
END_TEST

/* int cl_scandesc(int desc, const char **virname, unsigned long int *scanned, const struct cl_engine *engine, const struct cl_limits *limits, unsigned int options) */
START_TEST (test_cl_scandesc)
END_TEST

/* int cl_scanfile(const char *filename, const char **virname, unsigned long int *scanned, const struct cl_engine *engine, const struct cl_limits *limits, unsigned int options) */
START_TEST (test_cl_scanfile)
END_TEST

/* int cl_load(const char *path, struct cl_engine **engine, unsigned int *signo, unsigned int options) */
START_TEST (test_cl_load)
END_TEST

/* int cl_cvdverify(const char *file) */
START_TEST (test_cl_cvdverify)
END_TEST

/* int cl_statinidir(const char *dirname, struct cl_stat *dbstat) */
START_TEST (test_cl_statinidir)
END_TEST

/* int cl_statchkdir(const struct cl_stat *dbstat) */
START_TEST (test_cl_statchkdir)
END_TEST

/* void cl_settempdir(const char *dir, short leavetemps) */
START_TEST (test_cl_settempdir)
END_TEST

/* const char *cl_strerror(int clerror) */
START_TEST (test_cl_strerror)
END_TEST

Suite *test_cl_suite(void)
{
	Suite *s = suite_create("cl_api");
	TCase *tc_cl = tcase_create("cl_dup");

    suite_add_tcase (s, tc_cl);
    tcase_add_test(tc_cl, test_cl_free);
    tcase_add_test(tc_cl, test_cl_dup);
    tcase_add_test(tc_cl, test_cl_build);
    tcase_add_test(tc_cl, test_cl_debug);
    tcase_add_test(tc_cl, test_cl_retdbdir);
    tcase_add_test(tc_cl, test_cl_retver);
    tcase_add_test(tc_cl, test_cl_cvdfree);
    tcase_add_test(tc_cl, test_cl_statfree);
    tcase_add_test(tc_cl, test_cl_retflevel);
    tcase_add_test(tc_cl, test_cl_cvdhead);
    tcase_add_test(tc_cl, test_cl_cvdparse);
    tcase_add_test(tc_cl, test_cl_scandesc);
    tcase_add_test(tc_cl, test_cl_scanfile);
    tcase_add_test(tc_cl, test_cl_load);
    tcase_add_test(tc_cl, test_cl_cvdverify);
    tcase_add_test(tc_cl, test_cl_statinidir);
    tcase_add_test(tc_cl, test_cl_statchkdir);
    tcase_add_test(tc_cl, test_cl_settempdir);
    tcase_add_test(tc_cl, test_cl_strerror);

    return s;
}

int main(int argc, char **argv)
{
	int nf;
	Suite *s = test_cl_suite();
	SRunner *sr = srunner_create(s);

    srunner_set_log(sr, "test.log");
    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif /* HAVE_CHECK */
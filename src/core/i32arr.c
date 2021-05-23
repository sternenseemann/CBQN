#include "../core.h"

NOINLINE B m_cai32(usz ia, i32* a) {
  i32* rp; B r = m_i32arrv(&rp, ia);
  for (usz i = 0; i < ia; i++) rp[i] = a[i];
  return r;
}

static B m_i32slice(B p, i32* ptr) {
  I32Slice* r = mm_allocN(sizeof(I32Slice), t_i32slice);
  r->p = p;
  r->a = ptr;
  return tag(r, ARR_TAG);
}
static B i32arr_slice  (B x, usz s) {return m_i32slice(x                 , c(I32Arr  ,x)->a+s); }
static B i32slice_slice(B x, usz s) { B r = m_i32slice(inc(c(Slice,x)->p), c(I32Slice,x)->a+s); dec(x); return r; }

static B i32arr_get  (B x, usz n) { VTY(x,t_i32arr  ); return m_i32(c(I32Arr  ,x)->a[n]); }
static B i32slice_get(B x, usz n) { VTY(x,t_i32slice); return m_i32(c(I32Slice,x)->a[n]); }
static void i32arr_free(Value* x) { decSh(x); }
static bool i32arr_canStore(B x) { return q_i32(x); }

void i32arr_init() {
  ti[t_i32arr].get   = i32arr_get;   ti[t_i32slice].get   = i32slice_get;
  ti[t_i32arr].getU  = i32arr_get;   ti[t_i32slice].getU  = i32slice_get;
  ti[t_i32arr].slice = i32arr_slice; ti[t_i32slice].slice = i32slice_slice;
  ti[t_i32arr].free  = i32arr_free;  ti[t_i32slice].free  =    slice_free;
  ti[t_i32arr].visit = noop_visit;   ti[t_i32slice].visit =    slice_visit;
  ti[t_i32arr].print =    arr_print; ti[t_i32slice].print = arr_print;
  ti[t_i32arr].isArr = true;         ti[t_i32slice].isArr = true;
  ti[t_i32arr].arrD1 = true;         ti[t_i32slice].arrD1 = true;
  ti[t_i32arr].elType = el_i32;      ti[t_i32slice].elType = el_i32;
  ti[t_i32arr].canStore = i32arr_canStore;
  i32* tmp; bi_emptyIVec = m_i32arrv(&tmp, 0);
  gc_add(bi_emptyIVec);
}

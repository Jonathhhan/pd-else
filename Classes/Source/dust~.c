// Porres 2017

#include "m_pd.h"
#include "random.h"

static t_class *dust_class;

typedef struct _dust{
    t_object       x_obj;
    t_float        x_sample_dur;
    t_random_state x_rstate;
    t_float        x_density;
    t_float        x_lastout;
    int            x_id;
}t_dust;

static void dust_seed(t_dust *x, t_symbol *s, int ac, t_atom *av){
    random_init(&x->x_rstate, get_seed(s, ac, av, x->x_id));
}

static t_int *dust_perform(t_int *w){
    t_dust *x = (t_dust *)(w[1]);
    int n = (t_int)(w[2]);
    t_float *in1 = (t_float *)(w[3]);
    t_float *out = (t_sample *)(w[4]);
    t_float lastout = x->x_lastout;
    uint32_t *s1 = &x->x_rstate.s1;
    uint32_t *s2 = &x->x_rstate.s2;
    uint32_t *s3 = &x->x_rstate.s3;
    while(n--){
        t_float density = *in1++;
        t_float thresh = density * x->x_sample_dur;
        t_float scale = thresh > 0 ? 1./thresh : 0;
        t_float random = (t_float)(random_frand(s1, s2, s3) * 0.5 + 0.5);
        t_float output = random < thresh ? random * scale : 0;
        if(output != 0 && lastout != 0)
            output = 0;
        *out++ = lastout = output;
    }
    x->x_lastout = lastout;
    return(w+5);
}

static void dust_dsp(t_dust *x, t_signal **sp){
    x->x_sample_dur = 1./sp[0]->s_sr;
    dsp_add(dust_perform, 4, x, sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec);
}

static void *dust_new(t_symbol *s, int ac, t_atom *av){
    t_dust *x = (t_dust *)pd_new(dust_class);
    x->x_id = random_get_id();
    dust_seed(x, s, 0, NULL);
    if(av->a_type == A_SYMBOL){
        if(ac >= 2 && atom_getsymbol(av) == gensym("-seed")){
            t_atom at[1];
            SETFLOAT(at, atom_getfloat(av+1));
            ac-=2, av+=2;
            dust_seed(x, s, 1, at);
        }
    }
    x->x_lastout = 0;
    x->x_density = ac ? atom_getfloat(av) : 0;
    outlet_new(&x->x_obj, &s_signal);
    return(x);
}

void dust_tilde_setup(void){
    dust_class = class_new(gensym("dust~"), (t_newmethod)dust_new,
        0, sizeof(t_dust), CLASS_DEFAULT, A_GIMME, 0);
    CLASS_MAINSIGNALIN(dust_class, t_dust, x_density);
    class_addmethod(dust_class, (t_method)dust_dsp, gensym("dsp"), A_CANT, 0);
    class_addmethod(dust_class, (t_method)dust_seed, gensym("seed"), A_GIMME, 0);
}

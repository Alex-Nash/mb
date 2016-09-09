
#include "platform.h"
#include "xil_printf.h"

#define sqrt_3				1.7320508

struct ClarkInput_Type {
	u32 I_a;
	u32 I_b;
	u32 I_c;
};

struct ClarkOutput_Type {
	u32 I_alpha;
	u32 I_beta;
};
struct InvClarkInput_Type {
	u32 V_alpha;
	u32 V_beta;
};

struct InvClarkOutput_Type {
	u32 V_a;
	u32 V_b;
	u32 V_c;
};

struct ParcInput_Type {
	u32 I_alpha;
	u32 I_beta;
	u32 cos;
	u32 sin;
};
struct ParcOutput_Type {
	u32 I_d;
	u32 I_q;
};
struct InvParcInput_Type {
	u32 V_d;
	u32 V_q;
	u32 cos;
	u32 sin;
};
struct InvParcOutput_Type {
	u32 V_alpha;
	u32 V_beta;
};


void ClarkeTransformation (struct ClarkInput_Type *in_TreePhase, struct ClarkOutput_Type *out_StatOrthogonal);


void InverseClarkeTransformation(struct InvClarkInput_Type *in_StatOrthogonal, struct InvClarkOutput_Type *out_TreePhase);


void ParcTransformation (struct ParcInput_Type *in_Stationar, struct ParcOutput_Type *out_Rotate);


void InverseParcTransformation (struct InvParcInput_Type *in_Rotate, struct InvParcOutput_Type *out_Stationar);

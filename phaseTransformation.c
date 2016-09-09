#include "PhaseTransformation.h"


void ClarkeTransformation (	struct ClarkInput_Type *in_TreePhase,
														struct ClarkOutput_Type *out_StatOrthogonal)
{
	out_StatOrthogonal->I_alpha = in_TreePhase->I_a;
	out_StatOrthogonal->I_beta  = 1.0/sqrt_3 * in_TreePhase->I_a +
					2.0/sqrt_3 * in_TreePhase->I_b;
}

void InverseClarkeTransformation (struct InvClarkInput_Type *in_StatOrthogonal,
																	struct InvClarkOutput_Type *out_TreePhase)
{
	out_TreePhase->V_a = in_StatOrthogonal->V_alpha;
	out_TreePhase->V_b = -1.0/2.0 * in_StatOrthogonal->V_alpha +
					sqrt_3/2.0 * in_StatOrthogonal->V_beta;
	out_TreePhase->V_c = -1.0/2.0 * in_StatOrthogonal->V_alpha -
					sqrt_3/2.0 * in_StatOrthogonal->V_beta;
}

void ParcTransformation (	struct ParcInput_Type *in_Stationar,
													struct ParcOutput_Type *out_Rotate)
{
	out_Rotate->I_d = in_Stationar->I_alpha * in_Stationar->cos +
					in_Stationar->I_beta * in_Stationar->sin;
	out_Rotate->I_q = in_Stationar->I_beta * in_Stationar->cos  -
					in_Stationar->I_alpha * in_Stationar->sin;
}

void InverseParcTransformation (struct InvParcInput_Type *in_Rotate, 
																struct InvParcOutput_Type *out_Stationar)
{
	out_Stationar->V_alpha = in_Rotate->V_d * in_Rotate->cos -
					in_Rotate->V_q * in_Rotate->sin;
	out_Stationar->V_beta  = in_Rotate->V_q * in_Rotate->cos +
					in_Rotate->V_d * in_Rotate->sin;
}

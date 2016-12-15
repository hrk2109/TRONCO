#include <Rcpp.h>

using namespace Rcpp;

//' execute the get.dag.scores procedures
//' 
//' @param dataset A TRONCO dataset
//' @param adj_matrix An adj matrix
//' @param epos false positive rates
//' @param eneg false negative rates
// [[Rcpp::export]]
Rcpp::List C_get_dag_scores(Rcpp::NumericMatrix dataset,
                    Rcpp::NumericMatrix adj_matrix, 
                    double epos, 
                    double eneg ) {
    Rcout << "dataset\n" << dataset << "\n";
    Rcout << "adj.matrix \n" << adj_matrix << "\n";
    Rcout << "epos \n" << epos << "\n";
    Rcout << "eneg \n" << eneg << "\n";
    Rcout << "\n";
    Rcpp::NumericMatrix marginal_probs(3, 3);
    Rcpp::NumericMatrix joint_probs(3, 3);
    Rcpp::NumericMatrix prima_facie_model(3, 3);
    Rcpp::NumericMatrix prima_facie_null(3, 3);

    // Create the sampled dataset matrix
    Rcpp::NumericMatrix sampled_dataset(dataset.nrow(), dataset.ncol());
    
    // we need random number generator init value
    srand((unsigned)time(0));
    
    int row_id = 0;
    for (int i = 0; i < dataset.ncol(); i++) {
        row_id = rand() % dataset.ncol();
        sampled_dataset(_, i) = dataset(_, row_id);
    }

    Rcout << "sampled_dataset\n" << sampled_dataset << "\n";


    // Create output structure
    Rcpp::List scores = Rcpp::List::create(Rcpp::Named("marginal.probs") = marginal_probs,
        Rcpp::Named("joint.probs") = joint_probs,
        Rcpp::Named("prima.facie.model") = prima_facie_model,
        Rcpp::Named("prima.facie.null") = prima_facie_null);
    return scores;
}
